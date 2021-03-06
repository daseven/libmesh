// The libMesh Finite Element Library.
// Copyright (C) 2002-2017 Benjamin S. Kirk, John W. Peterson, Roy H. Stogner

// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.

// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA



#ifndef LIBMESH_CELL_PRISM15_H
#define LIBMESH_CELL_PRISM15_H

// Local includes
#include "libmesh/cell_prism.h"

namespace libMesh
{

/**
 * The \p Prism15 is an element in 3D composed of 15 nodes.
 * It is numbered like this:
 * \verbatim
 *   PRISM15:
 *                5
 *                o
 *               /:\
 *              / : \
 *             /  :  \
 *            /   :   \
 *        14 o    :    o 13
 *          /     :     \
 *         /      :      \
 *        /       o 11    \
 *     3 /        :        \4
 *      o---------o---------o
 *      |         :12       |
 *      |         :         |
 *      |         :         |
 *      |         o         |
 *      |        .2.        |
 *      |       .   .       |
 *    9 o      .     .      o 10
 *      |     .       .     |
 *      |  8 o         o 7  |
 *      |   .           .   |
 *      |  .             .  |
 *      | .               . |
 *      |.                 .|
 *      o---------o---------o
 *      0         6         1
 * \endverbatim
 *
 * \author Benjamin S. Kirk
 * \date 2003
 * \brief A 3D prismatic element with 15 nodes.
 */
class Prism15 libmesh_final : public Prism
{
public:

  /**
   * Constructor.  By default this element has no parent.
   */
  explicit
  Prism15 (Elem * p=libmesh_nullptr) :
    Prism(Prism15::n_nodes(), p, _nodelinks_data)
  {}

  /**
   * \returns \p PRISM15.
   */
  virtual ElemType type () const libmesh_override { return PRISM15; }

  /**
   * \returns 15.
   */
  virtual unsigned int n_nodes() const libmesh_override { return 15; }

  /**
   * \returns 1.
   */
  virtual unsigned int n_sub_elem() const libmesh_override { return 1; }

  /**
   * \returns \p true if the specified (local) node number is a vertex.
   */
  virtual bool is_vertex(const unsigned int i) const libmesh_override;

  /**
   * \returns \p true if the specified (local) node number is an edge.
   */
  virtual bool is_edge(const unsigned int i) const libmesh_override;

  /**
   * \returns \p true if the specified (local) node number is a face.
   */
  virtual bool is_face(const unsigned int i) const libmesh_override;

  /**
   * \returns \p true if the specified (local) node number is on the
   * specified side.
   */
  virtual bool is_node_on_side(const unsigned int n,
                               const unsigned int s) const libmesh_override;

  /**
   * \returns \p true if the specified (local) node number is on the
   * specified edge.
   */
  virtual bool is_node_on_edge(const unsigned int n,
                               const unsigned int e) const libmesh_override;

  /**
   * \returns \p true if the element map is definitely affine within
   * numerical tolerances.
   */
  virtual bool has_affine_map () const libmesh_override;

  /**
   * \returns SECOND.
   */
  virtual Order default_order() const libmesh_override { return SECOND; }

  /**
   * \returns \p Prism15::side_nodes_map[side][side_node] after doing some range checking.
   */
  virtual unsigned int which_node_am_i(unsigned int side,
                                       unsigned int side_node) const libmesh_override;

  /**
   * Builds a \p QUAD8 or \p TRI6 built coincident with face i.
   * The \p std::unique_ptr<Elem> handles the memory aspect.
   */
  virtual std::unique_ptr<Elem> build_side_ptr (const unsigned int i,
                                                bool proxy) libmesh_override;

  /**
   * Builds a \p EDGE3 or \p INFEDGE2 coincident with edge i.
   * The \p std::unique_ptr<Elem> handles the memory aspect.
   */
  virtual std::unique_ptr<Elem> build_edge_ptr (const unsigned int i) libmesh_override;

  virtual void connectivity(const unsigned int sc,
                            const IOPackage iop,
                            std::vector<dof_id_type> & conn) const libmesh_override;
  /**
   * \returns 2 for all \p n.
   */
  virtual unsigned int n_second_order_adjacent_vertices (const unsigned int) const libmesh_override
  { return 2; }

  /**
   * \returns The element-local number of the \f$ v^{th} \f$ vertex
   * that defines the \f$ n^{th} \f$ second-order node.
   *
   * \note \p n is counted as depicted above, \f$ 6 \le n < 15 \f$.
   */
  virtual unsigned short int second_order_adjacent_vertex (const unsigned int n,
                                                           const unsigned int v) const libmesh_override;

  /**
   * \returns The child number \p c and element-local index \p v of the
   * \f$ n^{th} \f$ second-order node on the parent element.  See
   * elem.h for further details.
   */
  virtual std::pair<unsigned short int, unsigned short int>
  second_order_child_vertex (const unsigned int n) const libmesh_override;

  /**
   * This maps the \f$ j^{th} \f$ node of the \f$ i^{th} \f$ side to
   * element node numbers.
   */
  static const unsigned int side_nodes_map[5][8];

  /**
   * This maps the \f$ j^{th} \f$ node of the \f$ i^{th} \f$ edge to
   * element node numbers.
   */
  static const unsigned int edge_nodes_map[9][3];

  /**
   * A specialization for computing the volume of a Prism15.
   */
  virtual Real volume () const libmesh_override;

protected:

  /**
   * Data for links to nodes.
   */
  Node * _nodelinks_data[15];



#ifdef LIBMESH_ENABLE_AMR

  /**
   * Matrix used to create the elements children.
   */
  virtual float embedding_matrix (const unsigned int i,
                                  const unsigned int j,
                                  const unsigned int k) const libmesh_override
  { return _embedding_matrix[i][j][k]; }

  /**
   * Matrix that computes new nodal locations/solution values
   * from current nodes/solution.
   */
  static const float _embedding_matrix[8][15][15];

  LIBMESH_ENABLE_TOPOLOGY_CACHES;

#endif

};

} // namespace libMesh

#endif // LIBMESH_CELL_PRISM15_H
