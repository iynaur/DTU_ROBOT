#!/bin/bash

base_path="/media/thso/Dataset1/models/"
save_path="/media/thso/Elements/Object_pose_dataset/"
scene_name=""
FILECOUNT=0
DIRCOUNT=-1

for dir in /media/thso/Dataset1/models/*
  do 
   # dir=${dir%*/}
    if [ -d "$dir" ]; then
        dirname=${dir##*/}
	echo "cd into ${dirname}"

        echo "./dti_move_object_frame  $dir/full/poisson_sampling.ply $dir/full/poisson_sampling_pca.ply"
	./dti_move_object_frame  $dir/full/poisson_sampling.ply $dir/full/poisson_sampling_pca.ply
	   
    fi
  done;




#echo $base_path
#./dtu_reconstruction -reconstruct /media/thso/My\ Passport/DTUData/scenes/scene_data/scene_054/ -stl

#for i in $(seq -f "%03g" 0 5)
#do
#   echo "Reconstruct scene $i"
#   scene_name="scene_$i" 
#   echo "execute: ../build/dtu_reconstruction -reconstruct $base_path$scene_name"/" -stl"
#   ../build/dtu_reconstruction -reconstruct $base_path$scene_name"/" -stl
#done