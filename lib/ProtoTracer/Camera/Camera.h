#pragma once

#include "CameraBase.h"
#include "Pixels\PixelGroup.h"

template<size_t pixelCount>
class Camera : public CameraBase {
private:
    PixelGroup<pixelCount>* pixelGroup;

public:
    Camera(Transform* transform, PixelGroup<pixelCount>* pixelGroup);
    Camera(Transform* transform, CameraLayout* cameraLayout, PixelGroup<pixelCount>* pixelGroup);

    PixelGroup<pixelCount>* GetPixelGroup() override;
    Vector2D GetCameraMinCoordinate() override;
    Vector2D GetCameraMaxCoordinate() override;
    Vector2D GetCameraCenterCoordinate() override;
};

#include "Camera.tpp"