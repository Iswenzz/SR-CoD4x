#!/bin/bash
export GAME="/d/Dev/CoD4/SDK"
export WORKDIR="mods/sr_speedrun/scripts"
export SERVER="start.sh"
export CLIENT="client.sh"

cd "$GAME/$WORKDIR"

./$SERVER
