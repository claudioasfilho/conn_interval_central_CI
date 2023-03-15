#!/bin/sh

cd GNU\ ARM\ v10.2.1\ -\ Debug/
make -j11 all

commander flash conn_interval_central_AM.hex -s 440060736