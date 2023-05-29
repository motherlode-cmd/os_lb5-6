#!/bin/bash
client_amount=$1

for (( counter=0; counter<client_amount; counter++ ))
do
	gnome-terminal -- sh -c "bash -c \"./udp_client udp_client$counter\""
done

