#include "entropy.h"

std::vector<double> Entropy::allele_vector(const Population& pop) {
  const size_t chromsize = pop[0].size();
  const size_t popsize   = pop.size();
  std::vector<double> gene_entropies(chromsize);
  double p_zero, p_one;

  for (size_t i=0; i < chromsize; i++) {
    unsigned int count_zeros = 0, count_ones = 0;

    for (const Chrom& chrom : pop) {
      if (chrom[i]) {
        count_ones++;
      } else {
        count_zeros++;
      }
    }

    p_zero = count_zeros / popsize;
    p_one  =  count_ones / popsize;
    gene_entropies[i] = p_zero*log2(p_zero) + p_one*log2(p_one);
  }

  return gene_entropies;
}

double Entropy::overall(const Population& population) {
  std::vector<double> genes = Entropy::allele_vector(population);
  double sum_entr = std::accumulate(genes.begin(), genes.end(), 0.0);
  return (double) (sum_entr / genes.size());
}