#include "bbsgd.h"

#include "basic.h"
#include "bbsys.h"

#include <sgd/sgd.h>

namespace {

void SGD_DECL errorHandler(SGD_String error, void *context) {
    RTEX(error);
}

void alert(BBStr* message) {
    sgd_Alert(message->c_str());
    delete message;
}

void createWindow(int width, int height, BBStr *title, int flags) {
	sgd_CreateWindow(width, height, title->c_str(), flags);
	delete title;
}

void setWebGPUBackend(BBStr* backend) {
    sgd_SetWebGPUBackend(backend->c_str());
    delete backend;
}

SGD_Texture loadTexture(BBStr* path, int format, int flags) {
	auto texture = sgd_LoadTexture(path->c_str(), format, flags);
	delete path;

	return texture;
}

SGD_Material loadPBRMaterial(BBStr* path) {
    auto material = sgd_LoadPBRMaterial(path->c_str());
    delete path;

    return material;
}

SGD_Material loadPrelitMaterial(BBStr* path) {
    auto material = sgd_LoadPrelitMaterial(path->c_str());
    delete path;

    return material;
}

SGD_Mesh loadMesh(BBStr* path) {
	auto mesh = sgd_LoadMesh(path->c_str());
	delete path;

	return mesh;
}

SGD_Skybox loadSkybox(BBStr* path, float roughness) {
	auto skybox = sgd_LoadSkybox(path->c_str(), roughness);
	delete path;

	return skybox;
}

SGD_Model loadModel(BBStr* path) {
	auto model = sgd_LoadModel(path->c_str());
	delete path;

	return model;
}

SGD_Model loadBonedModel(BBStr* path,int skinned) {
	auto model = sgd_LoadBonedModel(path->c_str(), skinned);
	delete path;

	return model;
}

void setMaterialTexture(SGD_Material material, BBStr* name, SGD_Texture texture) {
    sgd_SetMaterialTexture(material, name->c_str(), texture);
    delete name;
}

void setMaterialVector4f(SGD_Material material, BBStr* name, float x, float y, float z,float w) {
    sgd_SetMaterialVector4f(material, name->c_str(), x, y, z, w);
    delete name;
}

void setMaterialVector3f(SGD_Material material, BBStr* name, float x, float y, float z) {
    sgd_SetMaterialVector3f(material, name->c_str(), x, y, z);
    delete name;
}

void setMaterialVector2f(SGD_Material material, BBStr* name, float x, float y) {
    sgd_SetMaterialVector2f(material, name->c_str(), x, y);
    delete name;
}

void setMaterialFloat(SGD_Material material, BBStr* name, float n) {
    sgd_SetMaterialFloat(material, name->c_str(), n);
    delete name;
}

}

bool sgd_create(){
    sgd_Init();
    sgd_SetErrorHandler(errorHandler, nullptr);
    return true;
}

bool sgd_destroy(){
    sgd_Terminate();
    sgd_SetErrorHandler(nullptr, nullptr);
    return true;
}

bool sgd_link( void (*rtSym)( const char *sym, void *pc ) ){

    // System
    rtSym("Alert$message", alert);
    rtSym("%PollEvents", sgd_PollEvents);

    // Window
    rtSym("CreateWindow%width%height$title%flags", createWindow);
	rtSym("%KeyDown%key",sgd_KeyDown);
	rtSym("%KeyHit%key",sgd_KeyHit);
	rtSym("%GetChar",sgd_GetChar);
	rtSym("#MouseX", sgd_MouseX);
	rtSym("#MouseY", sgd_MouseY);
	rtSym("#MouseScrollX", sgd_MouseX);
	rtSym("#MouseScrollY", sgd_MouseY);
	rtSym("%MouseButtonDown%button",sgd_MouseButtonDown);
	rtSym("%MouseButtonHit%button",sgd_MouseButtonHit);
	rtSym("%GamepadConnected%gamepad",sgd_GamepadConnected);
	rtSym("%GamepadButtonDown%gamepad%button",sgd_GamepadButtonDown);
	rtSym("%GamepadButtonHit%gamepad%button",sgd_GamepadButtonHit);
	rtSym("#GamepadAxis%gamepad%axis",sgd_GamepadAxis);

    // Scene
    rtSym("SetWebGPUBackend$backend", setWebGPUBackend);
    rtSym("CreateScene", sgd_CreateScene);
    rtSym("SetSceneClearColor#red#green#blue#alpha", sgd_SetSceneClearColor);
    rtSym("SetSceneClearDepth#depth", sgd_SetSceneClearDepth);
    rtSym("SetSceneAmbientLightColor#red#green#blue#alpha", sgd_SetSceneAmbientLightColor);
    rtSym("SetSceneEnvTexture%texture", sgd_SetSceneEnvTexture);
    rtSym("RenderScene", sgd_RenderScene);
    rtSym("ClearScene", sgd_ClearScene);
    rtSym("Present", sgd_Present);

    // Texture
    rtSym("%LoadTexture$path%format%flags", loadTexture);

    // Material
    rtSym("%CreatePBRMaterial", sgd_CreatePBRMaterial);
    rtSym("%LoadPBRMaterial$path", loadPBRMaterial);
    rtSym("%CreatePrelitMaterial", sgd_CreatePrelitMaterial);
    rtSym("%LoadPrelitMaterial$path", loadPrelitMaterial);
    //
    rtSym("SetMaterialBlendMode%material%blendMode", sgd_SetMaterialBlendMode);
    rtSym("SetMaterialDepthFunc%material%depthFunc", sgd_SetMaterialDepthFunc);
    rtSym("SetMaterialCullMode%material%cullMode", sgd_SetMaterialCullMode);
    rtSym("SetMaterialTexture%material$name%texture", setMaterialTexture);
    rtSym("SetMaterialVector4f%material$name#x#y#z#a", setMaterialVector4f);
    rtSym("SetMaterialVector3f%material$name#x#y#z", setMaterialVector3f);
    rtSym("SetMaterialVector2f%material$name#x#y", setMaterialVector2f);
    rtSym("SetMaterialFloat%material$name#n", setMaterialFloat);

    // Mesh
	rtSym("%LoadMesh$path", loadMesh);
    rtSym("%CreateSphereMesh#radius%hSegs%vSegs%material", sgd_CreateSphereMesh);
	rtSym("%CreateBoxMesh#minX#minY#minZ#maxX#maxY#maxZ%material", sgd_CreateBoxMesh);
    rtSym("%CreateCylinderMesh#length#radius%segs%material", sgd_CreateCylinderMesh);
    rtSym("%CreateConeMesh#length#radius%segs%material", sgd_CreateConeMesh);
    rtSym("%CreateTorusMesh#outerRadius#innerRadius%outerSegs%innerSegs%material", sgd_CreateTorusMesh);
    rtSym("%CopyMesh%mesh", sgd_CopyMesh);
    rtSym("SetMeshCastsShadow%mesh%castsShadow", sgd_SetMeshCastsShadow);
    rtSym("%MeshCastsShadow%mesh", sgd_MeshCastsShadow);
    rtSym("UpdateMeshNormals%mesh", sgd_UpdateMeshNormals);
    rtSym("UpdateMeshTangents%mesh", sgd_UpdateMeshTangents);
	rtSym("FitMesh%mesh#minX#minY#minZ#maxX#maxY#maxZ%uniform", sgd_FitMesh);
    rtSym("TransformMeshTexCoords%mesh#scaleU#scaleV#offsetU#offsetV", sgd_TransformMeshTexCoords);
    rtSym("%FlipMesh%mesh", sgd_FlipMesh);

    // Skybox
	rtSym("%LoadSkybox$path#roughness", loadSkybox);
    rtSym("%CreateSkybox", sgd_CreateSkybox);
    rtSym("SetSkyboxTexture%skybox%texture", sgd_SetSkyboxTexture);
	rtSym("SetSkyboxRoughness%skybox#roughness", sgd_SetSkyboxRoughness);

    // Model
	rtSym("%LoadModel$path", loadModel);
	rtSym("%LoadBonedModel$path%skinned", loadBonedModel);
	rtSym("AnimateModel%model%animation#time%mode", sgd_AnimateModel);
    rtSym("%CreateModel", sgd_CreateModel);
    rtSym("SetModelMesh%model%mesh", sgd_SetModelMesh);
    rtSym("SetModelColor%model#red#green#blue#alpha", sgd_SetModelColor);
	rtSym("AnimateModel%model%animation#time%mode", sgd_AnimateModel);

    // Sprite
    rtSym("%CreateSprite", sgd_CreateSprite);
    rtSym("SetSpriteMaterial%sprite%material", sgd_SetSpriteMaterial);
    rtSym("SetSpriteColor%sprite#red#green#blue#alpha", sgd_SetSpriteColor);
    rtSym("SetSpriteRect%sprite#minX#minY#maxX#maxY", sgd_SetSpriteRect);

	// Camera
	rtSym("%CreatePerspectiveCamera", sgd_CreatePerspectiveCamera);
	rtSym("%CreateOrthographicCamera", sgd_CreateOrthographicCamera);
	rtSym("SetCameraFOV%camera#fov", sgd_SetCameraFOV);
	rtSym("SetCameraNear%camera#near", sgd_SetCameraNear);
	rtSym("SetCameraFar%camera#far", sgd_SetCameraFar);

    // Light
    rtSym("%CreateDirectionalLight", sgd_CreateDirectionalLight);
    rtSym("%CreatePointLight", sgd_CreatePointLight);
    rtSym("%CreateSpotLight", sgd_CreateSpotLight);
    rtSym("SetLightColor%light#red#green#blue#alpha", sgd_SetLightColor);
    rtSym("SetLightRange%light#range", sgd_SetLightRange);
    rtSym("SetLightFalloff%light#falloff", sgd_SetLightFalloff);
	rtSym("SetLightInnerConeAngle%light#angle", sgd_SetLightInnerConeAngle);
	rtSym("SetLightOuterConeAngle%light#angle", sgd_SetLightOuterConeAngle);
    rtSym("SetLightCastsShadow%light%castsShadow", sgd_SetLightCastsShadow);
    rtSym("LightCastsShadow%light", sgd_LightCastsShadow);

	// Entity
    rtSym("DestroyEntity%entity", sgd_DestroyEntity);
	rtSym("%CopyEntity%entity", sgd_CopyEntity);
	rtSym("SetEntityParent%entity%parent", sgd_SetEntityParent);
	rtSym("%EntityParent%entity", sgd_EntityParent);
	rtSym("SetEntityPosition%entity#x#y#z", sgd_SetEntityPosition);
	rtSym("SetEntityRotation%entity#rx#yr#zr", sgd_SetEntityRotation);
	rtSym("MoveEntity%entity#x#y#z", sgd_MoveEntity);
	rtSym("TurnEntity%entity#xr#yr#zr", sgd_TurnEntity);
	rtSym("TranslateEntity%entity#x#y#z", sgd_TranslateEntity);
	rtSym("RotateEntity%entity#xr#yr#zr", sgd_RotateEntity);

	rtSym("#EntityX%entity", sgd_EntityX);
	rtSym("#EntityY%entity", sgd_EntityY);
	rtSym("#EntityZ%entity", sgd_EntityZ);
	rtSym("#EntityRX%entity", sgd_EntityRX);
	rtSym("#EntityRY%entity", sgd_EntityRY);
	rtSym("#EntityRZ%entity", sgd_EntityRZ);

    return true;
}
