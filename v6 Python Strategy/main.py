#!/usr/bin/python3

import argparse
import sys
import os

from ProcessManager import ProcessManager
from Process import Process
from schedulers import fifo, priority, sjf, build_round_robin


BASICS_SCHEDULERS = {
    "fifo": fifo,
    "prio": priority,
    "priority": priority,
    "sjf": sjf
}

RR_SCHEDULERS = {"rr",  "round_robin"}


def read_process(file_name):
    '''
        Read a file with fake process descriptions.

        Each line represents
            (id, d, p, a, ios)
        where:
            id: identifier (unique)
            d: CPU usage phase duration
            p: priority
            a: arrived time
            ios: IO event queue
    '''
    processos = []
    for i in open(file_name, 'r').read().splitlines():
        aux = i.split()
        pross = [int(aux[0]), int(aux[1]), int(aux[2]), int(aux[3]), []]

        if len(aux) > 4:
            pross[4] = [int(i) for i in aux[4:]]

        processos.append(pross)
    return processos


def read_args():
    parser = argparse.ArgumentParser(description="description")
    parser.add_argument("-f", "--filename", type=str,
                        default="../resources/processos.txt")
    parser.add_argument("-io", "--time-io", type=int, default=1)
    parser.add_argument("-s", "--scheduler", type=str,
                        default=[], action="append")
    parser.add_argument("-sr", "--scheduler-rr", type=str,
                        default=[], action="append")
    parser.add_argument("-q", "--quantum", type=int, default=1)
    parser.add_argument("-v", "--version", action="version",
                        version="%(prog)s 1.0")
    parser.add_argument("-vr", "--verbose", default=False, action="store_true")
    parser.add_argument("-i", "--iterative", default=False, action="store_true")

    args = parser.parse_args()

    filename = args.filename
    if os.path.isfile("../resources/" + filename):
        filename = "../resources/" + filename
    else:
        raise Exception(f"File '{filename}' not exist")
    args.filename = filename

    if args.time_io <= 0:
        raise Exception("Argument 'time_io' must be greater then 0")

    if args.quantum <= 0:
        raise Exception("Argument 'quantum' must be greater then 0")

    args.scheduler_rr = args.scheduler_rr[::-1]
    scheduler_rr = []
    for s in args.scheduler_rr:
        scheduler_found = False
        for key, sc in BASICS_SCHEDULERS.items():
            if s in key:
                scheduler_rr.append(sc)
                scheduler_found = True
                break
    scheduler_rr = scheduler_rr or [fifo]

    schedulers = []
    for s in args.scheduler:
        scheduler_found = False
        for key, sc in BASICS_SCHEDULERS.items():
            if s in key:
                schedulers.append(sc)
                scheduler_found = True
                break
        if not scheduler_found:
            for key in RR_SCHEDULERS:
                if s in key:
                    # Last one is default
                    if len(args.scheduler_rr) > 1:
                        sc = scheduler_rr.pop()
                    else:
                        sc = scheduler_rr[0]
                    rr = build_round_robin(args.quantum, sc)
                    schedulers.append(rr)
                    scheduler_found = True
                    break
    args.scheduler = schedulers or [fifo]

    return args


if __name__ == "__main__":
    args = read_args()

    process_list = [Process(*p) for p in read_process(args.filename)]

    for p in process_list:
        p.time_io = args.time_io

    process_manager = ProcessManager(process_list)
    process_manager.enable_log(args.verbose)
    for sc in args.scheduler:
        process_manager.scheduler = sc
        process_manager.run()
    
    if args.iterative:
        process_manager.enable_log(True)
        process_manager.begin()
        while True:
            cmd = input(">")
            process_manager.execute()
            process_manager.next_clock()
