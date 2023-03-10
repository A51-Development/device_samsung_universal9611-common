/*
 * Copyright 2021 Soo Hwan Na "Royna"
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <thread>

#define KMSG_PATH "/proc/kmsg"
#define WRITE_KMSG "/data/debug/kmsg.txt"

#include <fstream>
#include <iostream>

static void copy_kmsg(void) {
  std::ifstream readfile(KMSG_PATH);
  std::ofstream writefile(WRITE_KMSG);
  while (1) { writefile << readfile.rdbuf(); }
}
static void copy_logcat(void) {
  system("/system/bin/logcat -b all -f /data/debug/logcat.txt");
}
int main(void) {
  std::thread kmsg(copy_kmsg);
  std::thread logcat(copy_logcat);
  kmsg.join(); // Block from exiting. since cp blocks too. 
	       // It is stopped when killed by init
  logcat.join();
  return 0;
}
