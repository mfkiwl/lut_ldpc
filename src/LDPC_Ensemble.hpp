/*!
 * \file LDPC_Ensemble.hpp
 * \brief Implementation of degree distribution objects for LDPC codes
 * \author Michael Meidlinger
 *
 * -------------------------------------------------------------------------
 *
 * Copyright (C) 2017 Michael Meidlinger - All Rights Reserved
 *
 * This file is part of lut_ldpc, a software suite for simulating and designing
 * LDPC decodes based on discrete Lookup Table (LUT) message passing
 *
 * lut_ldpc is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * lut_ldpc distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along
 * with lut_ldpc.  If not, see <http://www.gnu.org/licenses/>.
 *
 * -------------------------------------------------------------------------
 */

#ifndef LDPC_Ensemble_hpp
#define LDPC_Ensemble_hpp

#include "common.hpp"
#include <stdio.h>
#include <itpp/itbase.h>
#include <itpp/itcomm.h>

using namespace itpp;

namespace lut_ldpc{
    
//! Object for LDPC Degree distributions in sparse form
class LDPC_Ensemble{
private:
    /*!
     * Check consistency of ensemble.
     */
    inline void check_consistency();
private:
    vec rho;    //< check node degree distrivution (edge perspective) in sparse form
    vec lam;    //< variable node degree distrivution (edge perspective) in sparse form
    ivec degree_rho; //< nonzero check node degrees
    ivec degree_lam; //< nonzero variable node degrees
    int dv_act; //< number of nonzero variable node degrees
    int dc_act; //< number of nonzero check node degrees
    bool init_flag; //< true if the ensemble is defined completely and consistent
    /*!
     * \brief Accepted deviation to probability mass one without an error
     *
     * When setting any degree distributions, an input check is performed to see wether
     * the degree distributions sum to one, where deviations up to \c pmass_tolerance
     * don't cause an error. Note that the input will still be normalized before assignemnt.
     */
    static const double pmass_tolerance;
public:
    LDPC_Ensemble();
    //! LDPC ensemble based on nonsparse degree distribution vectors. First element = degree 1
    LDPC_Ensemble(const vec& l, const vec& r);
    //! LDPC ensemble based on sparse degree distribution vectors
    LDPC_Ensemble(const ivec& dl, const vec& l, const ivec& dr, const vec& r);
    //! Read LDPC ensemble from file
    LDPC_Ensemble(const std::string& filename);
    
    //! Read LDPC ensemble from .ens file
    void read(const std::string& filename);
    
    //! Write LDPC ensemble to .ens file
    void write(const std::string& filename) const;
    
    //! Export LDPC ensemble to .deg file (This kind of file is used by the PEG program)
    void export_deg(const std::string& filename) const;
    
    //! Get the rate of the ensemble
    double get_rate() const;
    
    //! Get variable node degree distribution (edge perspective) in sparse form (non zeros only)
    vec sget_lam()const;
    //! Get variable node degree distribution (node perspective) in sparse form (non zeros only)
    vec sget_Lam()const;
    //! Get variable node degree distribution and degrees (edge perspective) in sparse form (non zeros only). Returns the number of active degrees
    int sget_lam(vec& l, ivec& dl)const;
    
    //! Get check node degree distribution (edge perspective) in sparse form (non zeros only)
    vec sget_rho()const;
    //! Get check node degree distribution (node perspective) in sparse form (non zeros only)
    vec sget_Rho()const;
    //! Get check node degree distribution and degrees (edge perspective) in sparse form (non zeros only). Returns the number of active degrees
    int sget_rho(vec& r, ivec& dr)const;
    
    //! Get nonzero variable node degrees
    ivec sget_degree_rho()const;
    //! Get nonzero check node degrees
    ivec sget_degree_lam()const;
    
    //! Get number of nonzero variable node degrees
    int get_dv_act() const;
    //! Get number of nonzero check node degrees
    int get_dc_act() const;
    
    //! Return check node degree distribution (edge perspective) in non-sparse form. First index = degree 1
    vec get_chk_degree_dist() const;
    //! Return variable node degree distribution (edge perspective) in non-sparse form. First index = degree 1
    vec get_var_degree_dist() const;
    
    //! Set check node degree distribution (edge perspective) in non-sparse form. First index = degree 1
    void set_chk_degree_dist(const vec& r);
    //! Set variable node degree distribution (edge perspective) in non-sparse form. First index = degree 1
    void set_var_degree_dist(const vec& l);
    
    //! Set check node edge distribution in sparse form
    void sset_rho(vec r);
    //! Set variable node edge distribution in sparse form
    void sset_lam(vec l);
    
    //! Get probability mass of VN edge degree \c d
    double get_lam_of_degree(int d) const;
    //! Print properties of the LDPC ensemble
    friend std::ostream& operator<<(std::ostream &os, const LDPC_Ensemble &ens);
    
};

//! Print Information about the LDPC ensemble
std::ostream& operator<<(std::ostream &os, const LDPC_Ensemble &ens);

//! Calculate the LDPC ensemble from a parity check matrix
LDPC_Ensemble get_empirical_ensemble(const LDPC_Parity& H);

}

#endif /* LDPC_Ensemble_hpp */
