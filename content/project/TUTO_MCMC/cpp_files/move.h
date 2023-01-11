
#ifndef MOVE_H
#define MOVE_H

#include <Rcpp.h>

using namespace Rcpp;

List move_param(std::string moving, double curr_param, double fixed_param, double sd_proposal, Rcpp::NumericVector dat, double prior_mu, double prior_sd);

#endif
