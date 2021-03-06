/**
 *  @file VPSSMgr_Water_HKFT.h
 * Declaration file for a derived class that handles the calculation
 * of standard state thermo properties for real water and
 *  a set of species which have the HKFT equation of state
 * (see \ref mgrpdssthermocalc and
 * class \link Cantera::VPSSMgr_Water_HKFT VPSSMgr_Water_HKFT\endlink).
 */

// This file is part of Cantera. See License.txt in the top-level directory or
// at http://www.cantera.org/license.txt for license and copyright information.

#ifndef CT_VPSSMGR_WATER_HKFT_H
#define CT_VPSSMGR_WATER_HKFT_H

#include "VPSSMgr.h"

namespace Cantera
{
class PDSS_Water;

//! Manages standard state thermo properties for real water and a set of
//! species which have the HKFT equation of state.
class VPSSMgr_Water_HKFT : public VPSSMgr
{
public:
    //! Constructor
    /*!
     * @param vptp_ptr Pointer to the Variable pressure ThermoPhase object
     * @param spth     Pointer to the optional MultiSpeciesThermo object
     *                 that will handle the calculation of the reference
     *                 state thermodynamic coefficients.
     */
    VPSSMgr_Water_HKFT(VPStandardStateTP* vptp_ptr,
                       MultiSpeciesThermo* spth);

    /*! @name Thermodynamic Values for the Species Reference States
     *  There are also temporary variables for holding the species reference-
     *  state values of Cp, H, S, and V at the last temperature and reference
     *  pressure called. These functions are not recalculated if a new call is
     *  made using the previous temperature. All calculations are done within
     *  the routine  _updateRefStateThermo().
     */
    //@{

    virtual void getEnthalpy_RT_ref(doublereal* hrt) const;
    virtual void getGibbs_RT_ref(doublereal* grt) const;
    virtual void getGibbs_ref(doublereal* g) const;
    virtual void getEntropy_R_ref(doublereal* er) const;
    virtual void getCp_R_ref(doublereal* cpr) const;
    virtual void getStandardVolumes_ref(doublereal* vol) const;
    //@}

    virtual void setState_TP(doublereal T, doublereal P);
    virtual void setState_T(doublereal T);
    virtual void setState_P(doublereal P);

    /*! @name Setting the Internal State of the System
     *  All calls to change the internal state of the system's T and P
     *  are done through these routines
     *      - setState_TP()
     *      - setState_T()
     *      - setState_P()
     *
     *  These routine in turn call the following underlying virtual functions
     *
     *   - _updateRefStateThermo()
     *   - _updateStandardStateThermo()
     *
     *  An important point to note is that between calls the assumption
     *  that the underlying PDSS objects will retain their set Temperatures
     *  and Pressure CAN NOT BE MADE. For efficiency reasons, we may twiddle
     *  these to get derivatives.
     */
    //@{
    virtual void updateRefStateThermo() const;
private:
    virtual void _updateRefStateThermo() const;
    virtual void _updateStandardStateThermo();
    //@}

public:
    /*! @name Initialization Methods - For Internal use (VPStandardState)
     * The following methods are used in the process of constructing
     * the phase and setting its parameters from a specification in an
     * input file. They are not normally used in application programs.
     * To see how they are used, see importPhase().
     */
    //@{
    virtual void initThermoXML(XML_Node& phaseNode, const std::string& id);
    virtual PDSS* createInstallPDSS(size_t k, const XML_Node& speciesNode,
                                    const XML_Node* const phaseNode_ptr);
    //@}

private:
    //! Shallow pointer to the water object
    PDSS_Water* m_waterSS;

    //! Last reference temperature calculated
    /*!
     * Reference state calculations are totally separated from
     * standard state calculations.
     */
    mutable doublereal m_tlastRef;
};
}

#endif
