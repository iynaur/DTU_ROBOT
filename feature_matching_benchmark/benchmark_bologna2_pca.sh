#!/bin/bash

##########################################################################
# Test script for the Bologna 1 dataset which contains noise-free scenes #
##########################################################################

# Test parameters
dec=-1 # Decimation
rad=30,30,30,30 # Feature radius multiplier
res=6 # Feature resolution multiplier
thres=1 # Inlier threshold multipler, set to <= 0 for using 1 x mesh resolution

# Paths
exec_dir=build
exec_name=feature_matching_dataset
data_dir=~/workspace/datasets/bologna
output_dir=output/bologna2_pca

# Positionals
objects=`ls $data_dir/dataset1-2_models/3D_models/Stanford/*.ply -v1`
scenes=`ls $data_dir/dataset2_scenes/3D_models/Stanford/Random/*.ply -v1`
pose_dir=$data_dir/dataset2_scenes/3D_models/Stanford/Random
pose_separator="-"
pose_suffix=xf

# Options and flags
options="--pose-separator=$pose_separator --decimation=$dec --radius=$rad --resolution=$res --threshold=$thres --features=ecsad,rops,shot,usc --metrics=L2_RATIO"
flags="--verbose --pca"

# Start
$exec_dir/$exec_name "$objects" "$scenes" $pose_dir $pose_suffix $output_dir $options $flags $* #2> /dev/null

#gdb -ex run --args $exec_dir/$exec_name "$objects" "$scenes" $pose_dir $pose_suffix $output_dir $options $flags $*
