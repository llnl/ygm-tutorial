// Copyright 2019-2025 Lawrence Livermore National Security, LLC and other YGM
// Project Developers. See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: MIT

#include <ygm/comm.hpp>

//////////////////////////////////////////////////
// Empty sandbox for testing and debugging.     //
//////////////////////////////////////////////////

int main(int argc, char** argv) {
  ygm::comm world(&argc, &argv);

  world.welcome();

  return 0;
}