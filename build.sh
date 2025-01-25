#!/bin/bash

# Fonction pour afficher l'utilisation du script
usage() {
    echo "Usage: $0 [-ALL] [-windows] [-linux] [-android] [-ios] [-debug] [-release]"
    exit 1
}

# Vérifier si aucun argument n'a été passé
if [ $# -eq 0 ]; then
    usage
fi

# Variables par défaut
BUILD_ALL=false
BUILD_WINDOWS=false
BUILD_LINUX=false
BUILD_ANDROID=false
BUILD_IOS=false
BUILD_DEBUG=false
BUILD_RELEASE=false

# Traitement des arguments
while [[ $# -gt 0 ]]; do
    case $1 in
        -ALL)
            BUILD_ALL=true
            shift
            ;;
        -windows)
            BUILD_WINDOWS=true
            shift
            ;;
        -linux)
            BUILD_LINUX=true
            shift
            ;;
        -android)
            BUILD_ANDROID=true
            shift
            ;;
        -ios)
            BUILD_IOS=true
            shift
            ;;
        -debug)
            BUILD_DEBUG=true
            shift
            ;;
        -release)
            BUILD_RELEASE=true
            shift
            ;;
        *)
            echo "Unknown option: $1"
            usage
            ;;
    esac
done

# Si l'argument -ALL est passé, activer tous les builds
if [ "$BUILD_ALL" = true ]; then
    BUILD_WINDOWS=true
    BUILD_LINUX=true
    BUILD_ANDROID=true
    BUILD_IOS=true
    BUILD_DEBUG=true
    BUILD_RELEASE=true
fi

# Fonction pour effectuer le build de toutes les plateformes
build_all_platforms() {
    if [ "$BUILD_WINDOWS" = true ]; then
        build_windows
    fi
    if [ "$BUILD_LINUX" = true ]; then
        build_linux
    fi
    if [ "$BUILD_ANDROID" = true ]; then
        build_android
    fi
    if [ "$BUILD_IOS" = true ]; then
        build_ios
    fi
}

# Fonction de build pour Windows
build_windows() {
    echo "Building for Windows..."
    if [ "$BUILD_DEBUG" = true ]; then
        cmake -S . -B ./Build/Windows/Debug -DCMAKE_BUILD_TYPE=Debug
        cmake --build ./Build/Windows/Debug
    fi
    if [ "$BUILD_RELEASE" = true ]; then
        cmake -S . -B ./Build/Windows/Release -DCMAKE_BUILD_TYPE=Release
        cmake --build ./Build/Windows/Release
    fi
}

# Fonction de build pour Linux
build_linux() {
    echo "Building for Linux..."
    if [ "$BUILD_DEBUG" = true ]; then
        cmake -S . -B ./Build/Linux/Debug -DCMAKE_BUILD_TYPE=Debug
        cmake --build ./Build/Linux/Debug
    fi
    if [ "$BUILD_RELEASE" = true ]; then
        cmake -S . -B ./Build/Linux/Release -DCMAKE_BUILD_TYPE=Release
        cmake --build ./Build/Linux/Release
    fi
}

# Fonction de build pour Android
build_android() {
    echo "Building for Android..."
    if [ "$BUILD_DEBUG" = true ]; then
        cmake -S . -B ./Build/Android/Debug -DCMAKE_BUILD_TYPE=Debug
        cmake --build ./Build/Android/Debug
    fi
    if [ "$BUILD_RELEASE" = true ]; then
        cmake -S . -B ./Build/Android/Release -DCMAKE_BUILD_TYPE=Release
        cmake --build ./Build/Android/Release
    fi
}

# Fonction de build pour iOS
build_ios() {
    echo "Building for iOS..."
    if [ "$BUILD_DEBUG" = true ]; then
        cmake -S . -B ./Build/iOS/Debug -DCMAKE_BUILD_TYPE=Debug
        cmake --build ./Build/iOS/Debug
    fi
    if [ "$BUILD_RELEASE" = true ]; then
        cmake -S . -B ./Build/iOS/Release -DCMAKE_BUILD_TYPE=Release
        cmake --build ./Build/iOS/Release
    fi
}

# Exécution des builds en fonction des arguments
if [ "$BUILD_ALL" = true ]; then
    build_all_platforms
else
    if [ "$BUILD_WINDOWS" = true ]; then
        build_windows
    fi
    if [ "$BUILD_LINUX" = true ]; then
        build_linux
    fi
    if [ "$BUILD_ANDROID" = true ]; then
        build_android
    fi
    if [ "$BUILD_IOS" = true ]; then
        build_ios
    fi
fi

echo "Build process completed."
