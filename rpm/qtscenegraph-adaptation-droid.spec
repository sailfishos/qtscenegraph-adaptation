Name:       qtscenegraph-adaptation
Summary:    Scenegraph adaptation for Droid
Version:    0.8.1
Release:    1
License:    LGPLv2 with exception or GPLv3 or Qt Commercial
URL:        https://github.com/sailfishos/qtscenegraph-adaptation
Source0:    %{name}-%{version}.tar.bz2
BuildRequires:  qt5-qtcore-devel
BuildRequires:  qt5-qtgui-devel
BuildRequires:  qt5-qtdeclarative-devel
BuildRequires:  qt5-qtdeclarative-qtquick-devel
BuildRequires:  qt5-qmake

%description
This package contains system specific changes for the
Qt Quick Scene Graph.

%prep
%setup -q -n %{name}-%{version}

%build
export QTDIR=/usr/share/qt5
%qmake5 -config "surfaceformat programbinary hybristexture" DEFINES+=EGL_NO_X11

%install
%qmake5_install

%post -p /sbin/ldconfig
%postun -p /sbin/ldconfig

%files
%license LICENSE.LGPL
%license LGPL_EXCEPTION.txt
%license LICENSE.GPL
%{_libdir}/qt5/plugins/scenegraph/libcustomcontext.so
