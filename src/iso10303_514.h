/**
 * \file
 *
 * \brief Файл с определениями классов, соответствующих ГОСТ Р ИСО 10303-514-2007.
 */

#include "express_typelist.h"

namespace express {

  /**
   * \brief ENTITY advanced_brep_shape_representation (ГОСТ Р ИСО 10303-514-2007, 4.2)
   *
   * <B>Определение объекта на языке EXPRESS:</B>
   * \verbatim
    ENTITY advanced_brep_shape_representation
      SUBTYPE OF (shape_representation);
      WHERE
        WR1: SIZEOF(QUERY ( it <* SELF.items | (NOT (SIZEOF(['AIC_ADVANCED_BREP.MANIFOLD_SOLID_BREP',
                                               'AIC_ADVANCED_BREP.FACETED_BREP',
                                               'AIC_ADVANCED_BREP.MAPPED_ITEM',
                                               'AIC_ADVANCED_BREP.AXIS2_PLACEMENT_3D'] * TYPEOF(it)) = 1))))= 0;
        WR2: SIZEOF (QUERY (it <* SELF.items | (SIZEOF(['AIC.ADVANCED.BREP.MANIFOLD.SOLID.BREP',
                                               'AIC_ADVANCED_BREP.MAPPED_ITEM'] * TYPEOF(it)) = 1))) > 0;
        WR3: SIZEOF(QUERY (msb <* QUERY (it <* SELF.items | ('AIC_ADVANCED_BREP.MANIFOLD_SOLID_BREP' IN TYPEOF(it))) |
                                                (NOT (SIZEOF(QUERY (csh <* msb_shells(msb) |
                                                (NOT (SIZEOF(QUERY (fcs <* csh\connected_face_set.cfs_faces | (NOT (
                                               'AIC_ADVANCED_BREP.ADVANCED_FACE' IN TYPEOF(fcs))))) = 0))))= 0)))) = 0;
        WR4: SIZEOF (QUERY (msb <* QUERY (it <* items | ('AIC_ADVANCED_BREP.MANIFOLD_SOLID_BREP' IN TYPEOF(it))) |
                                                ('AIC_ADVANCED_BREP.ORIENTED_CLOSED_SHELL' IN
                                                TYPEOF(msb\manifold_solid_brep. outer)))) = 0;
        WR5: SIZEOF(QUERY ( brv <* QUERY ( it <* items | ('AIC_ADVANCED_BREP.BREP_WITH_VOIDS' IN TYPEOF(it))) | (NOT
                                                (SIZEOF(QUERY (csh <* brv\brep_with_voids.voids |
                                                (csh\oriented_closed_shell. orientation))) = 0))))= 0;
        WR6: SIZEOF(QUERY ( mi <* QUERY ( it <* items | ('AIC_ADVANCED_BREP.MAPPED_ITEM' IN TYPEOF(it))) |
                                                (NOT ('AIC_ADVANCED_BREP.ADVANCED_BREP_SHAPE_REPRESENTATION' IN
                                                TYPEOF(mi\mapped_item.mapping_source.mapped_representation)))))= 0;
     END_ENTITY;
   \endverbatim
   *
   * Расширенное граничное представление.
   * Объект advanced_brep_shape_representation является подтипом объекта shape_representation, в котором элементы представления являются
   * конкретизациями объектов manifold_solid_brep. Эти конкретизации отличаются от более общей В-rep модели тем, что в них для представления
   * геометрии граней и ребер должны использоваться только явные геометрические формы. Геометрия граней ограничена элементарными, изогнутыми
   * или би-сплайновыми поверхностями.
   */
  class advanced_brep_shape_representation : public shape_representation {
  public:

    // Конструктор
    advanced_brep_shape_representation(const std::string& Name, const representation_context* Context_of_items)
      : shape_representation(Name, Context_of_items) {
    }
  };
}