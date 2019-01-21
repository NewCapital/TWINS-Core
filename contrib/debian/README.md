
Debian
====================
This directory contains files used to package twinsd/twins-qt
for Debian-based Linux systems. If you compile twinsd/twins-qt yourself, there are some useful files here.

## twins: URI support ##


twins-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install twins-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your twinsqt binary to `/usr/bin`
and the `../../share/pixmaps/twins128.png` to `/usr/share/pixmaps`

twins-qt.protocol (KDE)

