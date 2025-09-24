#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

// enum StatisticsType
// {
//     avg,
//     min_max,
//     sum
// };

class Statistics
{
public:
    virtual ~Statistics() = default;
    virtual Results calculate(const Data& data) = 0;
};

class Avg : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        double avg = sum / data.size();

        return { StatResult("Avg", avg) };
    }
};

class MinMax : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double min = *(std::min_element(data.begin(), data.end()));
        double max = *(std::max_element(data.begin(), data.end()));

        return { StatResult("Min", min), StatResult("Max", max) };
    }
};

class Sum : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        return { StatResult("Sum", sum) };
    }
};

class Median : public Statistics
{
public:
    Results calculate(const Data& data) override
    {
        if (data.empty())
            return { StatResult("Median", 0.0) };

        std::vector<double> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());

        double median = sorted_data[sorted_data.size() / 2];
        return { StatResult("Median", median) };
    }
};

class DataAnalyzer
{
    std::shared_ptr<Statistics> statistics_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(std::shared_ptr<Statistics> statistics)
        : statistics_{statistics}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(std::shared_ptr<Statistics> new_stat)
    {
        statistics_ = new_stat;
    }

    void calculate()
    {
        Results results = statistics_->calculate(data_);
        results_.insert(results_.end(), results.begin(), results.end());
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

int main()
{
    auto avg = std::make_shared<Avg>();
    auto min_max = std::make_shared<MinMax>();
    auto sum = std::make_shared<Sum>();
    auto median = std::make_shared<Median>();
    
    DataAnalyzer da{avg};
    da.load_data("stats_data.dat");
    da.calculate();

    da.set_statistics(min_max);
    da.calculate();

    da.set_statistics(sum);
    da.calculate();

    da.set_statistics(median);
    da.calculate();

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_stats_data.dat");
    da.calculate();

    show_results(da.results());
}
