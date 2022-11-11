#ifndef GENERATOR_HPP

# define GENERATOR_HPP
# include "catch.hh"

extern "C" {
    #include "estimates.h"
}

namespace {

    class EstimatesGenerator : public Catch::Generators::IGenerator<t_estimate **> {
        std::minstd_rand                m_rand;
        std::uniform_int_distribution<> m_dist;
        std::vector<t_estimate>         m_estimates_internal;
        t_estimate                      **m_estimates;
    public:
        EstimatesGenerator(int low, int high):
            m_rand(std::random_device{}()),
            m_dist(low, high)
        {
            static_cast<void>(next());
        }

        t_estimate **const &get() const override;

        bool next() override {
            // clean up the list from before so no leaks
            m_estimates = NULL;
            
            // pre-allocate to prevent reallocations
            m_estimates_internal.reserve(m_dist.b());

            // generate a list of estimates using `m_dist(m_rand)`
            std::generate_n(std::back_inserter(m_estimates_internal), m_dist.b(), [this](){
                return ((t_estimate){ .name = "Something", .points = m_dist(m_rand)});
            });

            // [IMPORTANT] Add the two Estimates to be checked and shuffle to check that ordering does not matter
            m_estimates_internal.push_back((t_estimate){.name = "MrLowEstimate", m_dist.a() - 1});
            m_estimates_internal.push_back((t_estimate){.name = "MsHighEstimate", m_dist.b() + 1});
            shuffle_internal_list();

            // convert the vector to a list so we can use C functions to ASSERT
            internal_to_list();
            return true;
        }

    private:
        void    internal_to_list();
        void    shuffle_internal_list();
    };

    // Convert the `std::vector<t_estimates>` to a `t_estimates **` 
    void    EstimatesGenerator::internal_to_list() {
        int     idx;

        idx = 0;
        m_estimates = (t_estimate **)malloc(sizeof(t_estimate *) * (m_estimates_internal.size() + 1)); // NULL return not checked
        for (t_estimate estimate : m_estimates_internal) {
            t_estimate  *est = estimate_new(estimate.name, estimate.points);    // NULL return not checked
            m_estimates[idx] = est;
            idx++;
        }
        m_estimates[idx] = NULL;
    }

    void    EstimatesGenerator::shuffle_internal_list() {
        std::random_device  random_device;
        std::mt19937        generator(random_device());
    
        std::shuffle(m_estimates_internal.begin(), m_estimates_internal.end(), generator);
    }

    // Avoids -Wweak-vtables
    t_estimate **const& EstimatesGenerator::get() const {
        return m_estimates;      // Must be freed by the caller
    }

    // This helper function provides a nicer UX when instantiating the generator
    // Notice that it returns an instance of GeneratorWrapper<int>, which
    // is a value-wrapper around std::unique_ptr<IGenerator<int>>.
    Catch::Generators::GeneratorWrapper<t_estimate **> random(int low, int high) {
        return Catch::Generators::GeneratorWrapper<t_estimate **>(
            std::unique_ptr<Catch::Generators::IGenerator<t_estimate **>>(
                new EstimatesGenerator(low, high)
            )
        );
    }
}

#endif