/**
 * Copyright 2025 AntGroup CO., Ltd.
 * Copyright 2015 The etcd Authors
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

 // written by botu.wzy, inspired by etcd raft

#include <gtest/gtest.h>
#include "confstate.h"

namespace raftpb {
using namespace eraft;
static ConfState NewConfState(const std::vector<uint64_t>& voters,
                                        const std::vector<uint64_t>& learners = {},
                                        const std::vector<uint64_t>& votersOutgoing = {},
                                        const std::vector<uint64_t>& learnersNext = {}) {
    ConfState cs;
    *cs.mutable_voters() = {voters.begin(), voters.end()};
    *cs.mutable_learners() = {learners.begin(), learners.end()};
    *cs.mutable_voters_outgoing() = {votersOutgoing.begin(), votersOutgoing.end()};
    *cs.mutable_learners_next() = {learnersNext.begin(), learnersNext.end()};
    return cs;
}

TEST(raftpb, TestConfState_Equivalent) {
    struct testCase {
        ConfState cs;
        ConfState cs2;
        bool ok;
    };
    ConfState cs3;
    cs3.set_auto_leave(true);
    std::vector<testCase> testCases = {
        // Reordered voters and learners.
        {
                NewConfState({1, 2, 3},
                             {5, 4, 6},
                             {9, 8, 7},
                             {10, 20, 15}),
                NewConfState({1, 2, 3},
                             {4, 5, 6},
                             {7, 9, 8},
                             {20, 10, 15}),
                             true
        },
        // Not sensitive to nil vs empty slice.
        {
                {}, {}, true
        },
        // Non-equivalent voters.
        {
                NewConfState({ 1, 2, 3, 4 }),NewConfState({ 2, 1, 3 }), false
        },
        {
                NewConfState({ 1, 4, 3 }), NewConfState({ 2, 1, 3 }), false
        },
        // Non-equivalent learners.
        {
                NewConfState({ 1, 2, 3, 4 }),NewConfState({ 2, 1, 3 }),false
        },
        // Sensitive to AutoLeave flag.
        {
                cs3, {}, false
        }
    };
    for(auto& tc : testCases) {
        auto err = Equivalent(tc.cs, tc.cs2);
        EXPECT_EQ((err == nullptr), tc.ok);
    }
}

}