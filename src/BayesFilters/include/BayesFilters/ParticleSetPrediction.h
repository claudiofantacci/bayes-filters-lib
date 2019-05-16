/*
 * Copyright (C) 2016-2019 Istituto Italiano di Tecnologia (IIT)
 *
 * This software may be modified and distributed under the terms of the
 * BSD 3-Clause license. See the accompanying LICENSE file for details.
 */

#ifndef PARTICLESETPREDICTION_H
#define PARTICLESETPREDICTION_H

#include <BayesFilters/ParticleSet.h>

#include <Eigen/Dense>

namespace bfl {
    class ParticleSetPrediction;
}


class bfl::ParticleSetPrediction
{
public:
    virtual void predict(const ParticleSet& prev_state, ParticleSet& pred_state) = 0;
};

#endif /* PARTICLESETPREDICTION_H */
