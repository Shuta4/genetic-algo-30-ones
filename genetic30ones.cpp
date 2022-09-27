#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <random>

typedef std::vector<int> member_t;
typedef std::vector<member_t> population_t;

std::random_device rd;
std::mt19937 gen(rd());

std::ostream &operator<<(std::ostream &output, const member_t& member) {
	output << '[';
	for (auto it = member.begin(); it != member.end(); ++it) {
		output << *it;
		if (it != std::next(member.end(), -1)) {
			output << ", ";
		}
	}
	output << ']';
	return output;
}

std::ostream &operator<<(std::ostream &output, const population_t& population) {
	if (population.size() > 10) {
		output << "{ " << population.size() << " }";
	} else {
		output << "{\n";
		for (auto &member : population) {
			output << member << '\n';
		}
		output << '}';
	}
	return output;
}

void mutate(population_t &population, int n) {
	std::uniform_int_distribution<int> how_many_members(1, population.size());
	std::uniform_int_distribution<int> what_members(0, population.size() - 1);
	std::uniform_int_distribution<int> how_many_elements(1, n);
	std::uniform_int_distribution<int> what_elements(0, n - 1);

	for (int i = 0; i < how_many_members(gen); i++) {
		auto m = what_members(gen);
		for (int j = 0; j < how_many_elements(gen); j++) {
			auto e = what_elements(gen);
			if (population[m][e] == 0) {
				population[m][e] = 1;
			} else {
				population[m][e] = 0;
			}
		}
	}
}

member_t internalCrossover(
		const member_t &parent1, const member_t &parent2, int k) {

	member_t child(parent1.size());

	for (int i = 0; i < k; i++) {
		child[i] = parent1[i];
	}
	for (int i = k; i < parent2.size(); i++) {
		child[i] = parent2[i];
	}

	return child;
}

std::pair<member_t, member_t> crossover(
		const member_t &parent1, const member_t &parent2, int k) {

	return {
		internalCrossover(parent1, parent2, k),
		internalCrossover(parent2, parent1, k)
	};
}

int fitness(const member_t &member) {
	return std::accumulate(member.begin(), member.end(), 0);
}

void sort(population_t &population, bool reverse=false) {
	std::sort(population.begin(), population.end(),
		[reverse](const member_t &m1, const member_t &m2) {
			auto f1 = fitness(m1);
			auto f2 = fitness(m2);
			if (reverse) return f1 > f2;
			return f1 < f2;
		}
	);
}

int maxFitness(population_t &population) {
	sort(population, true);
	return fitness(population[0]);
}

void selection(population_t &population, int m) {
	sort(population, true);
	population.erase(std::next(population.begin(), m), population.end());
}

population_t createRandomPopulation(const int &n, const int &m) {
	std::uniform_int_distribution<int> distrib(0, 1);

	population_t population(m, member_t(n));
	for (auto &member : population) {
		for (auto &element : member) {
			element = distrib(gen);
		}
	}
	return population;
}

int main(int argc, char *argv[]) {
	std::cout << "Genetic Algo Solving Task About 30 Ones\n\n";

	int n(0), m(0);
	std::cout << "Enter number of x (n) and number of members in population (m) >> ";
	std::cin >> n >> m;

	auto population(createRandomPopulation(n, m));

	std::cout << "\nPopulation: " << population << '\n';

	std::uniform_int_distribution<int> distrib(1, n - 1);

	int iterations_count(0);
	auto max_fitness(maxFitness(population));
	while (max_fitness != n) {
		iterations_count++;
		std::cout << '\n' << iterations_count
			<< " iteration (max fitness = "
			<< max_fitness << "):\n";

		selection(population, m);
		std::cout << "Selectioned population: " << population << '\n';

		sort(population);
		for (int i = 0; i < m - 1; i += 2) {
			auto children = crossover(population[i], population[i + 1], distrib(gen));
			population.push_back(children.first);
			population.push_back(children.second);
		}

		std::cout << "Crossovered population: " << population << '\n';

		mutate(population, n);
		std::cout << "Let's there be mutation!\n"
			<< "Mutated population: " << population << '\n';

		max_fitness = maxFitness(population);
	}
	std::cout << "\nMission Complete in "
		<< iterations_count << " iterations!\n"
		<< "Final population: " << population << '\n';
}
