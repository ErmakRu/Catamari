#pragma once
//***************************************************************************************
// Camera.h by Frank Luna (C) 2011 All Rights Reserved.
//   
// Simple first person style camera class that lets the viewer explore the 3D scene.
//   -It keeps track of the camera coordinate system relative to the world space
//    so that the view matrix can be constructed.  
//   -It keeps track of the viewing frustum of the camera so that the projection
//    matrix can be obtained.
//***************************************************************************************

#ifndef CAMERA_H
#define CAMERA_H

#include "SimpleMath.h"
class Game;
class Camera
{
	//protected:
	//	DirectX::SimpleMath::Matrix viewProj;
public:
	Camera();
	~Camera();

	Game* game;
	// Get/Set world camera position.
	DirectX::SimpleMath::Vector4 GetPositionXM()const;
	DirectX::SimpleMath::Vector3 GetPosition()const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const DirectX::SimpleMath::Vector3& v);

	// Get camera basis vectors.
	DirectX::SimpleMath::Vector4 GetRightXM()const;
	DirectX::SimpleMath::Vector3 GetRight()const;
	DirectX::SimpleMath::Vector4 GetUpXM()const;
	DirectX::SimpleMath::Vector3 GetUp()const;
	DirectX::SimpleMath::Vector4 GetLookXM()const;
	DirectX::SimpleMath::Vector3 GetLook()const;

	// Get frustum properties.
	float GetNearZ()const;
	float GetFarZ()const;
	float GetAspect()const;
	float GetFovY()const;
	float GetFovX()const;

	// Get near and far plane dimensions in view space coordinates.
	float GetNearWindowWidth()const;
	float GetNearWindowHeight()const;
	float GetFarWindowWidth()const;
	float GetFarWindowHeight()const;

	// Set frustum.
	void SetLens(float fovY, float aspect, float zn, float zf);

	// Define camera space via LookAt parameters.
	void LookAt(DirectX::SimpleMath::Vector4 pos, DirectX::SimpleMath::Vector4 target, DirectX::SimpleMath::Vector4 worldUp);
	void LookAt(const DirectX::SimpleMath::Vector3& pos, const DirectX::SimpleMath::Vector3& target, const DirectX::SimpleMath::Vector3& up);

	// Get View/Proj matrices.
	DirectX::SimpleMath::Matrix View()const;
	DirectX::SimpleMath::Matrix Proj()const;
	DirectX::SimpleMath::Matrix ViewProj()const;

	// Strafe/Walk the camera a distance d.
	void Strafe(float d);
	void Walk(float d);

	// Rotate the camera.
	void Pitch(float angle);
	void RotateY(float angle);

	// After modifying camera position/orientation, call to rebuild the view matrix.
	void UpdateViewMatrix();

	bool IsOrthographic;
	//float OrthographicWidth;
	//float OrthographicHeight;
	//float FOV;
	//float AspectRatio;
	//float NearPlane;
	//float FarPlane;
	//DirectX::SimpleMath::Vector3 Position;
	//DirectX::SimpleMath::Vector3 Target;
	//DirectX::SimpleMath::Vector3 Up;
	//Camera();
	//void UpdateMatrix();
	//DirectX::SimpleMath::Matrix GetMatrix() const;

private:

	// Camera coordinate system with coordinates relative to world space.
	DirectX::SimpleMath::Vector3 mPosition;
	DirectX::SimpleMath::Vector3 mRight;
	DirectX::SimpleMath::Vector3 mUp;
	DirectX::SimpleMath::Vector3 mLook;

	// Cache frustum properties.
	float mNearZ;
	float mFarZ;
	float mAspect;
	float mFovY;
	float mNearWindowHeight;
	float mFarWindowHeight;

	// Cache View/Proj matrices.
	DirectX::SimpleMath::Matrix mView;
	DirectX::SimpleMath::Matrix mProj;
};

#endif // CAMERA_H
