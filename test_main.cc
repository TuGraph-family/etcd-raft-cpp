
/**
 * Copyright 2025 AntGroup CO., Ltd.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#include <iostream>
#include <gtest/gtest.h>
#include "util.h"
#include "raftpb/confstate.h"
#include "raftpb/confchange.h"
#include "quorum/joint.h"
#include "quorum/majority.h"
#include "quorum/quorum.h"
#include "tracker/inflights.h"
#include "tracker/state.h"
#include "tracker/progress.h"
#include "tracker/tracker.h"
#include "confchange/confchange.h"
#include "confchange/restore.h"
#include "read_only.h"
#include "describle.h"
#include "storage.h"
#include "log_unstable.h"
#include "log.h"
#include "raft.h"
#include "status.h"
#include "rawnode.h"

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc,argv);
    return RUN_ALL_TESTS();
}
