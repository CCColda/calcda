// clang-format off

%module Calcda
%{
	#include "../include/Intrinsic.hpp"
	#include "../include/Vector2.hpp"
	#include "../include/Vector3.hpp"
	#include "../include/Vector4.hpp"
	#include "../include/Matrix3.hpp"
	#include "../include/Matrix4.hpp"
	#include "../include/Geometry.hpp"
	#include "../include/Rotation.hpp"
	#include "../include/Integer.hpp"
%}

%nspace Calcda::Vector2;
%nspace Calcda::Vector3;
%nspace Calcda::Vector4;
%nspace Calcda::Matrix3;
%nspace Calcda::Matrix4;

%ignore Calcda::Vector2::operator*;
%ignore Calcda::Vector2::operator*=;
%ignore Calcda::Vector2::operator+;
%ignore Calcda::Vector2::operator+=;
%ignore Calcda::Vector2::operator-;
%ignore Calcda::Vector2::operator-=;
%ignore Calcda::Vector2::operator/;
%ignore Calcda::Vector2::operator/=;
%ignore Calcda::Vector2::operator=;
%ignore Calcda::Vector2::operator==;
%ignore Calcda::Vector2::operator!=;
%ignore Calcda::Vector2::getData() const;

%ignore Calcda::Vector3::operator*;
%ignore Calcda::Vector3::operator*=;
%ignore Calcda::Vector3::operator+;
%ignore Calcda::Vector3::operator+=;
%ignore Calcda::Vector3::operator-;
%ignore Calcda::Vector3::operator-=;
%ignore Calcda::Vector3::operator/;
%ignore Calcda::Vector3::operator/=;
%ignore Calcda::Vector3::operator=;
%ignore Calcda::Vector3::operator==;
%ignore Calcda::Vector3::operator!=;
%ignore Calcda::Vector3::getData() const;

%ignore Calcda::Vector4::operator*;
%ignore Calcda::Vector4::operator*=;
%ignore Calcda::Vector4::operator+;
%ignore Calcda::Vector4::operator+=;
%ignore Calcda::Vector4::operator-;
%ignore Calcda::Vector4::operator-=;
%ignore Calcda::Vector4::operator/;
%ignore Calcda::Vector4::operator/=;
%ignore Calcda::Vector4::operator=;
%ignore Calcda::Vector4::operator==;
%ignore Calcda::Vector4::operator!=;
%ignore Calcda::Vector4::getData() const;

%ignore Calcda::Matrix3::operator*;
%ignore Calcda::Matrix3::operator*=;
%ignore Calcda::Matrix3::operator+;
%ignore Calcda::Matrix3::operator+=;
%ignore Calcda::Matrix3::operator-;
%ignore Calcda::Matrix3::operator-=;
%ignore Calcda::Matrix3::operator/;
%ignore Calcda::Matrix3::operator/=;
%ignore Calcda::Matrix3::operator=;
%ignore Calcda::Matrix3::operator==;
%ignore Calcda::Matrix3::operator!=;
%ignore Calcda::Matrix3::getData() const;

%ignore Calcda::Matrix4::operator*;
%ignore Calcda::Matrix4::operator*=;
%ignore Calcda::Matrix4::operator+;
%ignore Calcda::Matrix4::operator+=;
%ignore Calcda::Matrix4::operator-;
%ignore Calcda::Matrix4::operator-=;
%ignore Calcda::Matrix4::operator/;
%ignore Calcda::Matrix4::operator/=;
%ignore Calcda::Matrix4::operator=;
%ignore Calcda::Matrix4::operator==;
%ignore Calcda::Matrix4::operator!=;
%ignore Calcda::Matrix4::getData() const;

%ignore Calcda::Polygon::Polygon(std::initializer_list<Vector2>);

%include "../include/Intrinsic.hpp"
%include "../include/Vector2.hpp"
%include "../include/Vector3.hpp"
%include "../include/Vector4.hpp"
%include "../include/Matrix3.hpp"
%include "../include/Matrix4.hpp"
%include "../include/Geometry.hpp"
%include "../include/Rotation.hpp"
%include "../include/Integer.hpp"