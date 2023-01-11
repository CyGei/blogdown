#ifndef MCMC_H
#define MCMC_H

#include <Rcpp.h>

using namespace Rcpp;

DataFrame mcmc(int n_iter, double init_mu, double init_sd, double sd_proposal_mu, double sd_proposal_sd, Rcpp::NumericVector dat, double prior_mu, double prior_sd);


#endif