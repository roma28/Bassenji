// This is an open source non-commercial project. Dear PVS-Studio, please check it.
//
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: http://www.viva64.com
//
// Copyright 2023 Roman Ishchenko
//
// Use of this source code is governed by an MIT-style
// license that can be found in the LICENSE file or at
// https://opensource.org/licenses/MIT.

#include <iostream>
#include <fstream>
#include <cxxopts.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/cfg/env.h>

#include <tao/pegtl.hpp>
#include <tao/pegtl/contrib/trace.hpp>

#include <IO/ReaderFactory.h>
#include <IO/WriterFactory.h>
#include <calculations/RMSDTrajectoryProcessor.h>
#include <IO/readers/grammar/xyz_grammar.h>

cxxopts::ParseResult parse_arguments(int argc, char* const argv[])
{
    cxxopts::Options opt("Bassenji", "A MD-based conformer generator");
    opt.allow_unrecognised_options();
    opt.add_options()("i,input", "Input file", cxxopts::value<std::string>())("o,output",
                                                                              "Output file",
                                                                              cxxopts::value<std::string>())("v,verbose",
                                                                                                             "Logging level",
                                                                                                             cxxopts::value<
                                                                                                                 int>()
                                                                                                                 ->default_value(
                                                                                                                     "2"))(
        "trace-parsing",
        "trace-parsing",
        cxxopts::value<bool>())("r,rmsd", "RMSD threshold", cxxopts::value<double>())("j,jobs",
                                                                                      "Number of parallel threads",
                                                                                      cxxopts::value<int>()
                                                                                          ->default_value("1"));

    cxxopts::ParseResult options = opt.parse(argc, argv);

    spdlog::set_level(static_cast<spdlog::level::level_enum>(options["verbose"].as<int>()));

    for (auto const& arg : options.arguments()) {
        spdlog::debug("Argument \"{0}\" with value \"{1}\" received", arg.key(), arg.value());
    }
    for (auto unknown_arg : options.unmatched()) {
        spdlog::warn("Unknown argument received {}", unknown_arg);
    }
    return options;
}

int main(int argc, char* argv[])
{
    cxxopts::ParseResult options = parse_arguments(argc, argv);
    spdlog::cfg::load_env_levels();

    spdlog::info("Bassenji started");

    if (options["trace-parsing"].as<bool>()) {
        auto in = tao::pegtl::file_input<>(options["input"].as<std::string>());
        tao::pegtl::standard_trace<xyz_file>(in);
        return 0;
    }

    auto r = ReaderFactory::GetReader("");
    auto traj = r->ReadFile(options["input"].as<std::string>());
    spdlog::debug("Parsing done: {0} frames in trajectory", traj.frames.size());

    RMSDTrajectoryProcessor p(options["rmsd"].as<double>());
    p.Process(traj, options["jobs"].as<int>());
    spdlog::debug("{0} uniques found", p.GetUniques().size());

    auto w = WriterFactory::GetWriter("");
    w->WriteFile(p.GetUniques(), options["output"].as<std::string>());
}

