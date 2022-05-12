# GITRACK

## What is GiTrack?

GiTrack is a simple tool to keep track of multiple repositories  that are under concurrent editing/development.

## Why GiTrack?

First of all: why not? 

Recently I've been working in an heavly parallel cuncurrent-develop environment: being on the engineering side rather thasn
on the development side, I had quite a difficult time with some engineers that would deliver either new releases or temporary versions.

Expecially on a broad project, keeping everything on track might not be easy. Unless, of course, you use GiTrack.

GiTrack allows you to define a project and check for any changes to said project with a simple command execution.


## Install

Installing GiTrack is quite easy; first clone the repository either via ssh or https protocol, then:

``` bash

cd gitrack 
sudo ./install 
```

and you are good to go.

You now have a **gitrack_installation** folder leveled with the gittrack

```
<parent-folder>
				|__gitrack
				|__gitrack_installation
```

## Using it

First of all you'll have to set up your **ProjectList** file:
There is already such a file in the installation folder, but it contains a sample repository of **[mad](git@github.com:franava/mad.git)** 
(another somewhat usefull script, feel free to check it out).

Fill this file up with your project Repositories and save-close it .
Each entry should contain 3 elements:
```
<repo name> <repo url> <status>
```
1. \<repo name>: is the name of the folder the is cloned in by default.
1. \<repo url>:  is the repo's url. t it will be used to clone/pull/fetch.
1. \<status>:	is the tracking status of the repo. it's defined as a single lower case character, either a **t**racked or **u**ntracked
While fetching-pulling a repo, if said repo is tracked, the script will look for any new branch, track it and pull info about it; 
that will not indeed happen if the repo is untracked. Still, any previously tracked branch will be fetched-pulled.

Once this is done, run
```bash
cd /path/to/gitrack_installation
./orchestrate [options]
```
The analisys log will be delivered in the log folder, and the components will be either downloaded (for first time addition) or fetch-pulled.
The option allows you to override the \<status>: simply add -u (or --untrack-all) to consider all repos as untracked; else, you can add -t (or --track-all)
and the script will interpret the status as tracked for each repo. This will not change the set up status in the **ProjectList** file.

## Uninstall

Uninstalling GiTrack is also quite easy; just run

```bash
cd /path/to/gitrack
./install -u
```
and that's done.



