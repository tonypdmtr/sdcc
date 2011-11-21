// Philipp Klaus Krause, philipp@informatik.uni-frankfurt.de, pkk@spth.de, 2011
//
// (c) 2011 Goethe-Universität Frankfurt
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option) any
// later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
//
// Optimal placement of bank switching instructions for named address spaces.

#ifndef SDCCNADDR_HH
#define SDCCNADDR_HH 1


#include <map>
#include <vector>
#include <sstream>
#include <fstream>

#include <boost/graph/graphviz.hpp>

#include "SDCCtree_dec.hpp"

extern "C"
{
#include "SDCCsymt.h"
#include "SDCCicode.h"
#include "SDCCBBlock.h"
#include "SDCCopt.h"
}

#ifdef HAVE_STX_BTREE_SET_H
#include <stx/btree_set.h>
#endif

typedef short int naddrspace_t; // Named address spaces. -1: Undefined, Others: see map.

#ifdef HAVE_STX_BTREE_SET_H
typedef stx::btree_set<naddrspace_t> naddrspaceset_t; // Faster than std::set
#else
typedef std::set<naddrspace_t> naddrspaceset_t;
#endif

struct assignment_naddr
{
  float s;
  naddrspaceset_t local;
  std::vector<naddrspace_t> global;

  bool operator<(const assignment_naddr& a) const
  {
    naddrspaceset_t::const_iterator i, ai, i_end, ai_end;

    i_end = local.end();
    ai_end = a.local.end();

    for (i = local.begin(), ai = a.local.begin();; ++i, ++ai)
      {
        if (i == i_end)
          return(true);
        if (ai == ai_end)
          return(false);

        if (*i < *ai)
          return(true);
        if (*i > *ai)
          return(false);

        if (global[*i] < a.global[*ai])
          return(true);
        if (global[*i] > a.global[*ai])
          return(false);
      }
  }
};

bool assignments_naddr_locally_same(const assignment_naddr &a1, const assignment_naddr &a2)
{
  if (a1.local != a2.local)
    return(false);

  naddrspaceset_t::const_iterator i, i_end;
  for (i = a1.local.begin(), i_end = a1.local.end(); i != i_end; ++i)
    if (a1.global[*i] != a2.global[*i])
      return(false);

  return(true);
}

struct cfg_node
{
  iCode *ic;
  naddrspaceset_t possible_naddrspaces;
};

typedef std::list<assignment_naddr> assignment_list_naddr_t;

struct tree_dec_naddr_node
{
  std::set<unsigned int> bag;
  assignment_list_naddr_t assignments;
};

typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, cfg_node, float> cfg_t; // The edge property is the cost of subdividing he edge and inserting a bank switching instruction.
typedef boost::adjacency_list<boost::vecS, boost::vecS, boost::bidirectionalS, tree_dec_naddr_node> tree_dec_naddr_t;

// A quick-and-dirty function to get the CFG from sdcc (a simplified version of the function from SDCCralloc.hpp).
void
create_cfg_naddr(cfg_t &cfg, iCode *start_ic, ebbIndex *ebbi)
{
  iCode *ic;

  std::map<int, unsigned int> key_to_index;
  {
    int i;

    for (ic = start_ic, i = 0; ic; ic = ic->next, i++)
      {
        boost::add_vertex(cfg);
        key_to_index[ic->key] = i;
        cfg[i].ic = ic;
      }
  }

  // Get control flow graph from sdcc.
  for (ic = start_ic; ic; ic = ic->next)
    {
      if (ic->op != GOTO && ic->op != RETURN && ic->op != JUMPTABLE && ic->next)
        boost::add_edge(key_to_index[ic->key], key_to_index[ic->next->key], 3.0f, cfg);

      if (ic->op == GOTO)
        boost::add_edge(key_to_index[ic->key], key_to_index[eBBWithEntryLabel(ebbi, ic->label)->sch->key], 6.0f, cfg);
      else if (ic->op == RETURN)
        boost::add_edge(key_to_index[ic->key], key_to_index[eBBWithEntryLabel(ebbi, returnLabel)->sch->key], 6.0f, cfg);
      else if (ic->op == IFX)
        boost::add_edge(key_to_index[ic->key], key_to_index[eBBWithEntryLabel(ebbi, IC_TRUE(ic) ? IC_TRUE(ic) : IC_FALSE(ic))->sch->key], 6.0f, cfg);
      else if (ic->op == JUMPTABLE)
        for (symbol *lbl = (symbol *)(setFirstItem (IC_JTLABELS (ic))); lbl; lbl = (symbol *)(setNextItem (IC_JTLABELS (ic))))
          boost::add_edge(key_to_index[ic->key], key_to_index[eBBWithEntryLabel(ebbi, lbl)->sch->key], 6.0f, cfg);
    }
}

// Annotate nodes of the control flow graph with the set of possible named address spaces active there.
void annotate_cfg_naddr(cfg_t &cfg)
{
  typedef typename boost::graph_traits<cfg_t>::vertex_descriptor vertex_t;

  std::map<const symbol *, naddrspace_t> sym_to_index;
  naddrspace_t na_max = -1;

  std::vector<bool> predetermined(boost::num_vertices (cfg), false);

  // Initialize the cfg vertices where there is information on the desired named address space.
  for (vertex_t i = 0; i < boost::num_vertices (cfg); i++)
    {
      const iCode *ic = cfg[i].ic;
      const symbol *addrspace;

      // We do not know the current named address space when entering a function or after calling one.
      if (ic->op == CALL || ic->op == PCALL || ic->op == FUNCTION)
        predetermined[i] = true;
      
      // Set the required named address spaces
      if (addrspace = getAddrspaceiCode (ic))
        {
          naddrspace_t na;

          if (sym_to_index.find (addrspace) == sym_to_index.end ())
            sym_to_index[addrspace] = ++na_max;
          na = sym_to_index[addrspace];

          cfg[i].possible_naddrspaces.insert (na);
          predetermined[i] = true;
        }
      else
        cfg[i].possible_naddrspaces.insert(-1);
    }

  // Extend.
  for(bool change = true; change; change = false)
    for (vertex_t i = 0; i < boost::num_vertices (cfg); i++)
    {
      if (predetermined[i])
        continue;

      size_t oldsize = cfg[i].possible_naddrspaces.size();
      {
        typedef typename boost::graph_traits<cfg_t>::out_edge_iterator n_iter_t;
        n_iter_t n, n_end;    
        for (boost::tie(n, n_end) = boost::out_edges(i, cfg);  n != n_end; ++n)
          {
            vertex_t v = boost::target(*n, cfg);
            cfg[i].possible_naddrspaces.insert(cfg[v].possible_naddrspaces.begin(), cfg[v].possible_naddrspaces.end());
          }
      }
      {
        typedef typename boost::graph_traits<cfg_t>::in_edge_iterator n_iter_t;
        n_iter_t n, n_end;    
        for (boost::tie(n, n_end) = boost::in_edges(i, cfg);  n != n_end; ++n)
          {
            vertex_t v = boost::source(*n, cfg);
            cfg[i].possible_naddrspaces.insert(cfg[v].possible_naddrspaces.begin(), cfg[v].possible_naddrspaces.end());
          }
      }

      if (oldsize != cfg[i].possible_naddrspaces.size())
          change = true;
    }
}

// Handle Leaf nodes in the nice tree decomposition
template <class T_t, class G_t>
void tree_dec_naddrswitch_leaf(T_t &T, typename boost::graph_traits<T_t>::vertex_descriptor t, const G_t &G)
{
  assignment_naddr a;
  assignment_list_naddr_t &alist = T[t].assignments;

  a.s = 0;
  a.global.resize(boost::num_vertices(G), -2);
  alist.push_back(a);
}

// Handle introduce nodes in the nice tree decomposition
template <class T_t, class G_t>
void tree_dec_naddrswitch_introduce(T_t &T, typename boost::graph_traits<T_t>::vertex_descriptor t, const G_t &G)
{
  typedef typename boost::graph_traits<T_t>::adjacency_iterator adjacency_iter_t;
  adjacency_iter_t c, c_end;
  assignment_list_naddr_t::iterator ai;
  boost::tie(c, c_end) = adjacent_vertices(t, T);

  assignment_list_naddr_t &alist2 = T[t].assignments;
  assignment_list_naddr_t &alist = T[*c].assignments;

  std::set<unsigned short> new_inst;
  std::set_difference(T[t].bag.begin(), T[t].bag.end(), T[*c].bag.begin(), T[*c].bag.end(), std::inserter(new_inst, new_inst.end()));
  unsigned short int i = *(new_inst.begin());

  for(ai = alist.begin(); ai != alist.end(); ++ai)
    {
      ai->local.insert(i);

      naddrspaceset_t::const_iterator ni, ni_end;
      for(ni = G[i].possible_naddrspaces.begin(), ni_end = G[i].possible_naddrspaces.end(); ni != ni_end; ++ni)
        {
          ai->global[i] = *ni;
          alist2.push_back(*ai);
        }
    }

  alist.clear();
}

// Handle forget nodes in the nice tree decomposition
template <class T_t, class G_t>
void tree_dec_naddrswitch_forget(T_t &T, typename boost::graph_traits<T_t>::vertex_descriptor t, const G_t &G)
{
  typedef typename boost::graph_traits<T_t>::adjacency_iterator adjacency_iter_t;
  adjacency_iter_t c, c_end;
  boost::tie(c, c_end) = adjacent_vertices(t, T);

  assignment_list_naddr_t &alist = T[t].assignments;

  std::swap(alist, T[*c].assignments);

  std::set<unsigned short int> old_inst;
  std::set_difference(T[*c].bag.begin(), T[*c].bag.end(), T[t].bag.begin(), T[t].bag.end(), std::inserter(old_inst, old_inst.end()));
  unsigned short int i = *(old_inst.begin());

  assignment_list_naddr_t::iterator ai, aif;

  std::cout << "tree_dec_naddrswitch_forget\n";

  // Restrict assignments (locally) to current variables.
  for (ai = alist.begin(); ai != alist.end(); ++ai)
    {
      ai->local.erase(i);
      {
        typedef typename boost::graph_traits<cfg_t>::out_edge_iterator n_iter_t;
        n_iter_t n, n_end;    
        for (boost::tie(n, n_end) = boost::out_edges(i, G);  n != n_end; ++n)
          {
            if (ai->local.find(boost::target(*n, G)) == ai->local.end() || ai->global[boost::target(*n, G)] == -1)
              continue;
            if (ai->global[boost::source(*n, G)] == ai->global[boost::target(*n, G)])
              continue;
            ai->s += G[*n];
          }
      }
      {
        typedef typename boost::graph_traits<cfg_t>::in_edge_iterator n_iter_t;
        n_iter_t n, n_end;    
        for (boost::tie(n, n_end) = boost::in_edges(i, G);  n != n_end; ++n)
          {
            if (ai->local.find(boost::source(*n, G)) == ai->local.end() || ai->global[boost::target(*n, G)] == -1)
              continue;
            if (ai->global[boost::source(*n, G)] == ai->global[boost::target(*n, G)])
              continue;
            ai->s += G[*n];
          }
      }
    }

  alist.sort();

  // Collapse (locally) identical assignments.
  for (ai = alist.begin(); ai != alist.end();)
    {
      aif = ai;

      for (++ai; ai != alist.end() && assignments_naddr_locally_same(*aif, *ai);)
        {
          if (aif->s > ai->s)
            {
              alist.erase(aif);
              aif = ai;
              ++ai;
            }
          else
            {
              alist.erase(ai);
              ai = aif;
              ++ai;
            }
        }
    }
}

// Handle join nodes in the nice tree decomposition
template <class T_t, class G_t>
void tree_dec_naddrswitch_join(T_t &T, typename boost::graph_traits<T_t>::vertex_descriptor t, const G_t &G)
{
  typedef typename boost::graph_traits<T_t>::adjacency_iterator adjacency_iter_t;
  adjacency_iter_t c, c_end, c2, c3;
  boost::tie(c, c_end) = adjacent_vertices(t, T);

  c2 = c;
  ++c;
  c3 = c;

  assignment_list_naddr_t &alist1 = T[t].assignments;
  assignment_list_naddr_t &alist2 = T[*c2].assignments;
  assignment_list_naddr_t &alist3 = T[*c3].assignments;

  alist2.sort();
  alist3.sort();

  assignment_list_naddr_t::iterator ai2, ai3;
  for (ai2 = alist2.begin(), ai3 = alist3.begin(); ai2 != alist2.end() && ai3 != alist3.end();)
    {
      if (assignments_naddr_locally_same(*ai2, *ai3))
        {
          ai2->s += ai3->s;
          for (size_t i = 0; i < ai2->global.size(); i++)
            ai2->global[i] = ((ai2->global[i] != -2) ? ai2->global[i] : ai3->global[i]);
          alist1.push_back(*ai2);
          ++ai2;
          ++ai3;
        }
      else if (*ai2 < *ai3)
        {
          ++ai2;
          continue;
        }
      else if (*ai3 < *ai2)
        {
          ++ai3;
          continue;
        }
    }

  alist2.clear();
  alist3.clear();
}

template <class T_t, class G_t>
void tree_dec_naddrswitch_nodes(T_t &T, typename boost::graph_traits<T_t>::vertex_descriptor t, const G_t &G)
{
  typedef typename boost::graph_traits<T_t>::adjacency_iterator adjacency_iter_t;

  adjacency_iter_t c, c_end;
  typename boost::graph_traits<T_t>::vertex_descriptor c0, c1;

  boost::tie(c, c_end) = adjacent_vertices(t, T);

  switch (out_degree(t, T))
    {
    case 0:
      tree_dec_naddrswitch_leaf(T, t, G);
      break;
    case 1:
      c0 = *c;
      tree_dec_naddrswitch_nodes(T, c0, G);
      T[c0].bag.size() < T[t].bag.size() ? tree_dec_naddrswitch_introduce(T, t, G) : tree_dec_naddrswitch_forget(T, t, G);
      break;
    case 2:
      c0 = *c++;
      c1 = *c;
      tree_dec_naddrswitch_nodes(T, c0, G);
      tree_dec_naddrswitch_nodes(T, c1, G);
      tree_dec_naddrswitch_join(T, t, G);
      break;
    default:
      std::cerr << "Not nice.\n";
      break;
    }
}

template <class T_t, class G_t>
void tree_dec_address_switch(T_t &T, const G_t &G)
{
  tree_dec_naddrswitch_nodes(T, find_root(T), G);

  const assignment_naddr &winner = *(T[find_root(T)].assignments.begin());

  std::cout << "Winner: ";
  for(unsigned int i = 0; i < boost::num_vertices(G); i++)
  {
  	std::cout << "(" << i << ", " << int(winner.global[i]) << ") ";
  }
  std::cout << "\n";
  std::cout << "Cost: " << winner.s << "\n";
  std::cout.flush();
}

// Dump cfg, with numbered nodes, show posible address spaces at each node.
void dump_cfg_naddr(const cfg_t &cfg)
{
  std::ofstream dump_file((std::string(dstFileName) + ".dumpnaddrcfg" + currFunc->rname + ".dot").c_str());

  std::string *name = new std::string[num_vertices(cfg)];
  for (unsigned int i = 0; i < boost::num_vertices(cfg); i++)
    {
      std::ostringstream os;
      os << i << ", " << cfg[i].ic->key << ": ";
      naddrspaceset_t::const_iterator n;
      for (n = cfg[i].possible_naddrspaces.begin(); n != cfg[i].possible_naddrspaces.end(); ++n)
        os << *n << " ";
      name[i] = os.str();
    }
  boost::write_graphviz(dump_file, cfg, boost::make_label_writer(name));
  delete[] name;
}

#endif

