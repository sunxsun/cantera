/**
 *  @file SpeciesThermo.h
 *  Virtual base class for the calculation of multiple-species thermodynamic
 *  property managers and text for the spthermo module (see \ref spthermo 
 *  and class \link Cantera::SpeciesThermo SpeciesThermo\endlink).
 *
 *  We also describe the doxygen module spthermo  (see \ref spthermo )
 */

/*
 * $Author$
 * $Revision$
 * $Date$
 */

// Copyright 2001  California Institute of Technology


#ifndef CT_SPECIESTHERMO_H
#define CT_SPECIESTHERMO_H

#include "ct_defs.h"

namespace Cantera {

  /**
   * @defgroup spthermo Species Standard-State Thermodynamic Properties
   *
   * To compute the thermodynamic properties of multicomponent
   * solutions, it is necessary to know something about the
   * thermodynamic properties of the individual species present in
   * the solution. Exactly what sort of species properties are
   * required depends on the thermodynamic model for the
   * solution. For a gaseous solution (i.e., a gas mixture), the
   * species properties required are usually ideal gas properties at
   * the mixture temperature and at a reference pressure (often 1
   * atm or 1 bar). For other types of solutions, however, it may
   * not be possible to isolate the species in a "pure" state. For
   * example, the thermodynamic properties of, say, Na+ and Cl- in
   * saltwater are not easily determined from data on the properties
   * of solid NaCl, or solid Na metal, or chlorine gas. In this
   * case, the solvation in water is fundamental to the identity of
   * the species, and some other reference state must be used. One
   * common convention for liquid solutions is to use thermodynamic
   * data for the solutes for the limit of infinite dilution in the
   * pure solvent; another convention is to reference all properties
   * to unit molality.
   *
   * In defining these standard states for species in a phase, we make
   * the following definition. A reference state is a standard state
   * of a species in a phase limited to one pressure, the reference
   * pressure. The reference state specifies the dependence of all
   * thermodynamic functions as a function of the temperature, in
   * between a minimum temperature and a maximum temperature. The
   * reference state also specifies the molar volume of the species
   * as a function of temperature. The molar volume is a thermodynamic
   * function.
   * A full standard state does the same thing as a reference state,
   * but specifies the thermodynamics functions at all pressures.
   *
   * Whatever the conventions used by a particular solution model,
   * means need to be provided to compute the species properties in 
   * the reference state. Class SpeciesThermo is the base class
   * for a family of classes that compute properties of all
   * species in a phase in their reference states, for a range of temperatures.
   * Note, the pressure dependence of the species thermodynamic functions is not
   * handled by this particular species thermodynamic model. %SpeciesThermo
   * calculates the thermodynamic values of all species in a single
   * phase during each call. 
   *
   *
   *  The following classes inherit from %SpeciesThermo. Each of these classes
   *  handle multiple species, usually all of the species in a phase.
   *
   *   - NasaThermo          in file NasaThermo.h
   *      - This is a two zone model, with each zone consisting of a 7 
   *        coefficient Nasa Polynomial format.
   *      .
   *   - ShomateThermo       in file ShomateThermo.h
   *      - This is a two zone model, with each zone consisting of a 7 
   *        coefficient Shomate Polynomial format.
   *      .
   *   - SimpleThermo        in file SimpleThermo.h
   *      - This is a one-zone constant heat capacity model.
   *      .
   *   - GeneralSpeciesThermo in file GeneralSpeciesThermo.h
   *      - This is a general model. Each species is handled separately
   *        via a vector over SpeciesThermoInterpType classes.
   *      . 
   *   - SpeciesThermo1        in file SpeciesThermoMgr.h
   *   - SpeciesThermoDuo      in file SpeciesThermoMgr.h
   *      - This is a combination of two SpeciesThermo types.
   *      .
   *   .
   *
   * The class SpeciesThermoInterpType is a pure virtual base class for
   * calculation of thermodynamic functions for a single species
   * in its reference state.
   *  The following classes inherit from %SpeciesThermoInterpType
   *   - NasaPoly1          in file NasaPoly1.h
   *      - This is a one zone model,  consisting of a 7 
   *        coefficient Nasa Polynomial format.
   *      .
   *   - NasaPoly2          in file NasaPoly2.h
   *      - This is a two zone model, with each zone consisting of a 7 
   *        coefficient Nasa Polynomial format.
   *      .
   *   - ShomatePoly        in file ShomatePoly.h
   *      - This is a one zone model, consisting of a 7 
   *        coefficient Shomate Polynomial format.
   *      .
   *   - ShomatePoly2       in file ShomatePoly.h
   *      - This is a two zone model, with each zone consisting of a 7 
   *        coefficient Shomate Polynomial format.
   *      .
   *   - ConstCpPoly        in file ConstCpPoly.h
   *      - This is a one-zone constant heat capacity model.
   *      .
   *   - Mu0Poly            in file Mu0Poly.h
   *      - This is a multizoned model. The chemical potential is given
   *        at a set number of temperatures. Between each temperature
   *        the heat capacity is treated as a constant.
   *      .
   *   .
   */
  //@{

  //////////////////////// class SpeciesThermo ////////////////////

  
  //! Pure Virtual base class for the species thermo manager classes.
  /*!
   *  This class defines the interface which all subclasses must implement. 
   *
   * Class %SpeciesThermo is the base class
   * for a family of classes that compute properties of a set of 
   * species in their reference state at a range of temperatures.
   * Note, the pressure dependence of the reference state is not
   * handled by this particular species standard state model.
   */
  class SpeciesThermo {
    
  public:

    //! Constructor
    SpeciesThermo() {}

    //! Destructor
    virtual ~SpeciesThermo() {}

    
    //! Install a new species thermodynamic property
    //! parameterization for one species.  
    /*!
     *
     * @param name      Name of the species
     * @param index     The 'update' method will update the property 
     *                  values for this species 
     *                  at position i index in the property arrays.  
     * @param type      int flag specifying the type of parameterization to be
     *                 installed. 
     * @param c        vector of coefficients for the parameterization. 
     *                 This vector is simply passed through to the
     *                 parameterization constructor.
     * @param minTemp  minimum temperature for which this parameterization
     *                 is valid.
     * @param maxTemp  maximum temperature for which this parameterization
     *                 is valid.
     * @param refPressure standard-state pressure for this 
     *                    parameterization. 
     * @see speciesThermoTypes.h 
     */
    virtual void install(std::string name, int index, int type, 
			 const doublereal* c, 
			 doublereal minTemp,
			 doublereal maxTemp,
			 doublereal refPressure)=0;

    
    //! Compute the reference-state properties for all species.
    /*!
     * Given temperature T in K, this method updates the values of
     * the non-dimensional heat capacity at constant pressure,
     * enthalpy, and entropy, at the reference pressure, Pref
     * of each of the standard states.
     *
     * @param T       Temperature (Kelvin)
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     */
    virtual void update(doublereal T, 
			doublereal* cp_R, 
			doublereal* h_RT, 
			doublereal* s_R) const=0;

    
    //! Like update(), but only updates the single species k.
    /*!
     * @param k       species index
     * @param T       Temperature (Kelvin)
     * @param cp_R    Vector of Dimensionless heat capacities.
     *                (length m_kk).
     * @param h_RT    Vector of Dimensionless enthalpies.
     *                (length m_kk).
     * @param s_R     Vector of Dimensionless entropies.
     *                (length m_kk).
     *
     */
    virtual void update_one(int k, doublereal T, 
			    doublereal* cp_R, 
			    doublereal* h_RT, 
			    doublereal* s_R) const {
      update(T, cp_R, h_RT, s_R);
    }

    //! Minimum temperature.
    /*!
     * If no argument is supplied, this
     * method returns the minimum temperature for which \e all
     * parameterizations are valid. If an integer index k is
     * supplied, then the value returned is the minimum
     * temperature for species k in the phase.
     *
     * @param k    Species index
     */ 
    virtual doublereal minTemp(int k=-1) const =0;

    //! Maximum temperature.
    /*!
     * If no argument is supplied, this
     * method returns the maximum temperature for which \e all
     * parameterizations are valid. If an integer index k is
     * supplied, then the value returned is the maximum
     * temperature for parameterization k.
     *
     * @param k  Species Index
     */
    virtual doublereal maxTemp(int k=-1) const =0;
    
    //! The reference-state pressure for species k.
    /*!
     *
     * returns the reference state pressure in Pascals for
     * species k. If k is left out of the argument list,
     * it returns the reference state pressure for the first
     * species.
     * Note that some SpeciesThermo implementations, such
     * as those for ideal gases, require that all species
     * in the same phase have the same reference state pressures.
     *
     * @param k Species Index
     */
    virtual doublereal refPressure(int k=-1) const =0;

    //! This utility function reports the type of parameterization
    //! used for the species with index number index.
    /*!
     *
     * @param index  Species index
     */
    virtual int reportType(int index = -1) const = 0;

    
    //! This utility function reports back the type of 
    //! parameterization and all of the parameters for the species, index.
    /*!
     * @param index     Species index
     * @param type      Integer type of the standard type
     * @param c         Vector of coefficients used to set the
     *                  parameters for the standard state.
     * @param minTemp   output - Minimum temperature
     * @param maxTemp   output - Maximum temperature
     * @param refPressure output - reference pressure (Pa).
     */
    virtual void reportParams(int index, int &type, 
			      doublereal * const c, 
			      doublereal &minTemp, 
			      doublereal &maxTemp, 
			      doublereal &refPressure) const =0;

    //! Modify parameters for the standard state
    /*!
     * @param index Species index
     * @param c     Vector of coefficients used to set the
     *              parameters for the standard state.
     */
    virtual void modifyParams(int index, doublereal *c) = 0;

  };
  //@}
}

#endif

