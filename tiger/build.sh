#!/bin/sh
set -e

which docker > /dev/null
if [ $? -ne 0 ]; then
    echo docker is not installed, please install it
    return 1
fi

if [ -z "$(grep "\(docker\(.*\)$USER\)" /etc/group)" ]; then
    echo $USER is not in the docker group, adding it..
    sudo usermod -aG docker $USER
    echo svp reboot gngn
    return 1
fi

if [ -z "$(docker images | grep registry.lrde.epita.fr/tc-sid)" ]; then
    echo building the docker image..
    sleep 3
    if [ -d buildenv ]; then
        rm -rf buildenv
    fi
    git clone https://gitlab.lre.epita.fr/tiger/buildenv.git
    docker build -f buildenv/Dockerfile-sid -t registry.lrde.epita.fr/tc-sid buildenv/
    if [ -z "$(docker images | grep registry.lrde.epita.fr/tc-sid)" ]; then
        echo failed to build the docker image hmm
        return 1
    fi
    rm -rf buildenv
fi

docker run --rm -it -v $PWD:/tc --workdir /tc registry.lrde.epita.fr/tc-sid $@
