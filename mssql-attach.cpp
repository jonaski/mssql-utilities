/*
   MSSQL Utilities
   Copyright 2019, Jonas Kvinge <jonas@jkvinge.net>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.

 */

#include "config.h"

#include <cstdio>
#include <string>
#include <iostream>
#include <fstream>

#ifdef EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;
#else
#include <filesystem>
namespace fs = std::filesystem;
#endif
#include <boost/algorithm/string.hpp>

int main(int, char**) {

  std::string out_filename;
#ifdef MSSQL_DETACH
    out_filename = "mssql-detach.sql";
#else
    out_filename = "mssql-attach.sql";
#endif

  std::cout << "' MSSQL Utilities (C) 2019 Jonas Kvinge\n";
  std::cout << "' This program is free software, released under GPL.\n";
  std::cout << "' For more information vist https://github.com/jonaski/\n";

  if (fs::exists(out_filename)) {
    fs::remove(out_filename);
  }

  std::ofstream out_file;
  out_file.open(out_filename);

  for (const auto &i : fs::directory_iterator(".")) {
#ifdef EXPERIMENTAL_FILESYSTEM
    if (!fs::is_regular_file(i)) continue;
#else
    if (!i.is_regular_file()) continue;
#endif
    if (!i.path().has_extension()) continue;
    std::string extension = i.path().extension().u8string();
    boost::algorithm::to_lower(extension);
    if (extension != ".mdf") continue;
    std::string dbname = i.path().stem().u8string();
    if (dbname == "MSDBData" || dbname == "master" || dbname == "model" || dbname == "tempdb") continue;
    std::string filename = i.path().filename().u8string();
    std::string this_path = fs::current_path().u8string();
    std::string command;
#ifdef MSSQL_DETACH
      command = "exec sp_detach_db '" + dbname + "'";
#else
      command = "exec sp_attach_db @dbname = '" + dbname + "', @filename1='" + this_path + "\\" + filename + "', @filename2='" + this_path + "\\" + dbname + "_log.ldf" + "'";
#endif
    std::cout << command << "\n";
    if (out_file.is_open()) {
      out_file << command << + "\n";
    }
  }

  if (out_file.is_open()) {
    out_file.close();
  }

  return 0;

}
