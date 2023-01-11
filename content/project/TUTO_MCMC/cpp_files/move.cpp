
#include <Rcpp.h>
#include "cpp_model.h"
using namespace Rcpp;

// [[Rcpp::export]]
Rcpp::List move_param(std::string moving,
                      double curr_param,
                      double fixed_param,
                      double sd_proposal,
                      Rcpp::NumericVector dat,
                      double prior_mu,
                      double prior_sd) 
{
  
  // printing info
  Rcpp::Rcout << "moving " << moving << std::endl;
  Rcpp::Rcout << "curr_param: " << curr_param << std::endl;
  Rcpp::Rcout << "fixed_param: " << fixed_param << std::endl;
  
  
  // Sample a new value for the parameter from a normal distribution with mean equal to the current parameter value and standard deviation equal to sd_proposal
  double new_param = R::rnorm(curr_param, sd_proposal);
  
  // Print out the new value of the parameter
  Rcpp::Rcout << "new_param: " << new_param << std::endl;
  
  // Declare ratio_post outside if{} statement to compile
  double ratio_post;
  
  // Calculate the ratio of the posterior probabilities for the new and current values of the parameter
  if(moving == "mu"){
    
    ratio_post = log_posterior(dat, new_param, fixed_param, prior_mu, prior_sd) - log_posterior(dat, curr_param, fixed_param, prior_mu, prior_sd);
    
  } else if(moving == "sd") {
    
    ratio_post = log_posterior(dat, fixed_param, new_param, prior_mu, prior_sd) - log_posterior(dat, fixed_param, curr_param, prior_mu, prior_sd);
    
  }else{
    
    ratio_post = R_NegInf;
    
  }
  
  // Initialize the correction term to 0 (0 because our proposal distribution is symetrical)
  double correction = 0.0;
  
  // Calculate the acceptance probability for the new value of the parameter  
  double p_accept = ratio_post + correction;
  Rcpp::Rcout << "p_accept: " << p_accept << std::endl;
  
  // Sample a uniform random value between 0 and 1
  double tmp = log(Rcpp::runif(1)[0]);
  
  // If the random value is less than the acceptance probability, accept the new value of the parameter   
  double updated_param;
  double accept;
  if(tmp < p_accept) 
  {
    updated_param = new_param;
    accept = 1;
    Rcpp::Rcout << "accept" << std::endl << std::endl;
    
  }else // reject
  {
    updated_param = curr_param; 
    accept = 0;
    Rcpp::Rcout << "reject" << std::endl << std::endl;
  }
  
  // Return a List containing the updated value of the parameter and a binary value indicating whether the new value was accepted or rejected
  return Rcpp::List::create(Rcpp::Named("updated_param") = updated_param,
                            Rcpp::Named("accept") = accept);
}