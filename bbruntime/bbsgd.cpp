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

SGD_Font loadFont(BBStr* path, float height) {
	auto font = sgd_LoadFont(path->c_str(), height);
	delete path;

	return font;
}

float fontTextWidth(SGD_Font font, BBStr* text) {
	auto r = sgd_FontTextWidth(font, text->c_str());
	delete text;
	return r;
}

float get2DTextWidth(BBStr* text) {
	auto r = sgd_Get2DTextWidth(text->c_str());
	delete text;
	return r;
}

SGD_Image loadImage(BBStr* path, int frameCount) {
	auto r = sgd_LoadImage(path->c_str(), frameCount);
	delete path;
	return r;
}

void draw2DText(BBStr* text, float x, float y) {
	sgd_Draw2DText(text->c_str(), x, y);
	delete text;
}

SGD_Sound loadSound(BBStr* path) {
	auto sound = sgd_LoadSound(path->c_str());
	delete path;

	return sound;
}

}

bool sgd_create(){
	sgd_Init();
	sgd_SetErrorHandler(errorHandler, nullptr);
	return true;
}

bool sgd_destroy(){
	sgd_Terminate();
	return true;
}

bool sgd_link( void (*rtSym)( const char *sym, void *pc ) ){

	// System
	rtSym("SetWebGPUBackend$backend", setWebGPUBackend);
	rtSym("Alert$message", alert);
	rtSym("%DesktopWidth", sgd_DesktopWidth);
	rtSym("%DesktopHeight", sgd_DesktopHeight);
	rtSym("%PollEvents", sgd_PollEvents);

	// Window
	rtSym("CreateWindow%width%height$title%flags", createWindow);
	rtSym("DestroyWindow", sgd_DestroyWindow);
	rtSym("%WindowWidth", sgd_WindowWidth);
	rtSym("%WindowHeight", sgd_WindowHeight);

	// User input
	rtSym("%KeyDown%key", sgd_KeyDown);
	rtSym("%KeyHit%key", sgd_KeyHit);
	rtSym("%GetChar", sgd_GetChar);
	rtSym("FlushChars", sgd_FlushChars);
	rtSym("#MouseX", sgd_MouseX);
	rtSym("#MouseY", sgd_MouseY);
	rtSym("#MouseZ", sgd_MouseZ);
	rtSym("#MouseVX", sgd_MouseVX);
	rtSym("#MouseVY", sgd_MouseVY);
	rtSym("#MouseVZ", sgd_MouseVZ);
	rtSym("SetMouseZ#z", sgd_SetMouseZ);
	rtSym("SetMouseCursorMode%cursorMode", sgd_SetMouseCursorMode);
	rtSym("%MouseButtonDown%button", sgd_MouseButtonDown);
	rtSym("%MouseButtonHit%button", sgd_MouseButtonHit);
	rtSym("%GamepadConnected%gamepad", sgd_GamepadConnected);
	rtSym("%GamepadButtonDown%gamepad%button", sgd_GamepadButtonDown);
	rtSym("%GamepadButtonHit%gamepad%button", sgd_GamepadButtonHit);
	rtSym("#GamepadAxis%gamepad%axis", sgd_GamepadAxis);

	// Texture
	rtSym("%LoadTexture$path%format%flags", loadTexture);

	// Material
	rtSym("%CreatePBRMaterial", sgd_CreatePBRMaterial);
	rtSym("%LoadPBRMaterial$path", loadPBRMaterial);
	rtSym("%CreatePrelitMaterial", sgd_CreatePrelitMaterial);
	rtSym("%LoadPrelitMaterial$path", loadPrelitMaterial);
	rtSym("SetMaterialBlendMode%material%blendMode", sgd_SetMaterialBlendMode);
	rtSym("SetMaterialDepthFunc%material%depthFunc", sgd_SetMaterialDepthFunc);
	rtSym("SetMaterialCullMode%material%cullMode", sgd_SetMaterialCullMode);
	rtSym("SetMaterialVector4f%material$name#x#y#z#a", setMaterialVector4f);
	rtSym("SetMaterialVector3f%material$name#x#y#z", setMaterialVector3f);
	rtSym("SetMaterialVector2f%material$name#x#y", setMaterialVector2f);
	rtSym("SetMaterialFloat%material$name#n", setMaterialFloat);
	rtSym("SetMaterialTexture%material$name%texture", setMaterialTexture);

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
	rtSym("TFormMesh%mesh#tx#ty#tz#rx#ry#rz#sx#sy#sz", sgd_TFormMesh);
	rtSym("TFormMeshTexCoords%mesh#scaleU#scaleV#offsetU#offsetV", sgd_TFormMeshTexCoords);
	rtSym("TransformMesh%mesh#tx#ty#tz#rx#ry#rz#sx#sy#sz", sgd_TransformMesh);	// @deprecated.
	rtSym("TransformMeshTexCoords%mesh#scaleU#scaleV#offsetU#offsetV", sgd_TransformMeshTexCoords);	// @deprecated.
	rtSym("%FlipMesh%mesh", sgd_FlipMesh);

	// Mesh editing - vertices
	rtSym("%CreateMesh%vertexCount%meshFlags", sgd_CreateMesh);
	rtSym("%ResizeVertices%mesh%vertexCount", sgd_ResizeVertices);
	rtSym("%VertexCount%mesh", sgd_VertexCount);
	rtSym("%AddVertex%mesh#x#y#z#nx#ny#nz#s#t", sgd_AddVertex);
	rtSym("SetVertex%mesh%vertex#x#y#z#nx#ny#nz#s#t", sgd_SetVertex);
	rtSym("SetVertexPosition%mesh%vertex#x#y#z",sgd_SetVertexPosition);
	rtSym("SetVertexNormal%mesh%vertex#nx#ny#nz",sgd_SetVertexNormal);
	rtSym("SetVertexTangent%mesh%vertex#tx#ty#tz#tw",sgd_SetVertexTangent);
	rtSym("SetVertexTexCoords%mesh%vertex#s#t",sgd_SetVertexTexCoords);
	rtSym("SetVertexColor%mesh%vertex#r#g#b#a",sgd_SetVertexColor);

	// Surfaces
	rtSym("%CreateSurface%mesh%triangleCount%material", sgd_CreateSurface);
	rtSym("ResizeTriangles%surface%triangleCount", sgd_ResizeTriangles);
	rtSym("%TriangleCount%surface", sgd_TriangleCount);
	rtSym("%AddTriangle%surface%vertex0%vertex1%vertex2", sgd_AddTriangle);
	rtSym("SetTriangle%surface%triangle%vertex0%vertex1%vertex2", sgd_SetTriangle);

	// Font
	rtSym("%LoadFont$path#height", loadFont);
	rtSym("#FontTextWidth%font$text", fontTextWidth);
	rtSym("#FontHeight%font", sgd_FontHeight);

	// Image
	rtSym("%LoadImage$path%frameCount", loadImage);
	rtSym("SetImageBlendMode%image%blendMode", sgd_SetImageBlendMode);
	rtSym("SetImageSpriteRect%image#minX#minY#maxX#maxY", sgd_SetImageSpriteRect);
	rtSym("SetImageSpriteViewMode%image%viewMode", sgd_SetImageSpriteViewMode);
	rtSym("SetImageDraw2DHandle%image#x#y", sgd_SetImageDraw2DHandle);
	rtSym("%ImageWidth%image", sgd_ImageWidth);
	rtSym("%ImageHeight%image", sgd_ImageHeight);
	rtSym("%ImageFrameCount%image", sgd_ImageFrameCount);

	// 2D Overlay state
	rtSym("Set2DFillColor#red#green#blue#alpha", sgd_Set2DFillColor);
	rtSym("Set2DFillMaterial%material", sgd_Set2DFillMaterial);
	rtSym("Set2DFillEnabled%enabled", sgd_Set2DFillEnabled);
	rtSym("Set2DOutlineColor#red#green#blue#alpha", sgd_Set2DOutlineColor);
	rtSym("Set2DOutlineWidth#width", sgd_Set2DOutlineWidth);
	rtSym("Set2DOutlineEnabled%enabled", sgd_Set2DOutlineEnabled);
	rtSym("Set2DLineWidth#width", sgd_Set2DLineWidth);
	rtSym("Set2DPointSize#size", sgd_Set2DPointSize);
	rtSym("Set2DFont%font", sgd_Set2DFont);
	rtSym("Set2DTextColor#red#green#blue#alpha", sgd_Set2DTextColor);
	rtSym("#Get2DTextWidth$text", get2DTextWidth);
	rtSym("#Get2DFontHeight", sgd_Get2DFontHeight);

	// 2D Overlay drawing
	rtSym("Clear2D", sgd_Clear2D);
	rtSym("Push2DLayer", sgd_Push2DLayer);
	rtSym("Pop2DLayer", sgd_Pop2DLayer);
	rtSym("Draw2DPoint#x#y", sgd_Draw2DPoint);
	rtSym("Draw2DLine#x0#y0#x1#y1", sgd_Draw2DLine);
	rtSym("Draw2DRect#minX#minY#maxX#maxY", sgd_Draw2DRect);
	rtSym("Draw2DOval#minX#minY#maxX#maxY", sgd_Draw2DOval);
	rtSym("Draw2DImage%image#x#y#frame", sgd_Draw2DImage);
	rtSym("Draw2DText$text#x#y", draw2DText);
	
	// Audio
	rtSym("%LoadSound$path", loadSound);
	rtSym("PlaySound%sound", sgd_PlaySound);
	rtSym("CueSound%sound", sgd_CueSound);
	rtSym("SetAudioVolume%sound#volume", sgd_SetAudioVolume);
	rtSym("SetAudioPan%sound#pan", sgd_SetAudioPan);
	rtSym("SetAudioPitchScale%audio#scale", sgd_SetAudioPitchScale);
	rtSym("SetAudioPaused%audio%paused", sgd_SetAudioPaused);
	rtSym("%AudioValid%audio", sgd_AudioValid);
	rtSym("StopAudio%audio", sgd_StopAudio);

	// Scene
	rtSym("CreateScene", sgd_CreateScene);
	rtSym("ClearScene", sgd_ClearScene);
	rtSym("SetSceneAmbientLightColor#red#green#blue#alpha", sgd_SetSceneAmbientLightColor);
	rtSym("SetSceneClearColor#red#green#blue#alpha", sgd_SetSceneClearColor);
	rtSym("SetSceneClearDepth#depth", sgd_SetSceneClearDepth);
	rtSym("SetSceneEnvTexture%texture", sgd_SetSceneEnvTexture);
	rtSym("RenderScene", sgd_RenderScene);
	rtSym("Present", sgd_Present);
	rtSym("#FPS",sgd_FPS);
	rtSym("#RPS",sgd_RPS);

	// Entity
	rtSym("SetEntityEnabled%entity%enabled", sgd_SetEntityEnabled);
	rtSym("%EntityEnabled%entity", sgd_EntityEnabled);
	rtSym("SetEntityVisible%entity%visible", sgd_SetEntityVisible);
	rtSym("%EntityVisible%entity", sgd_EntityVisible);
	rtSym("DestroyEntity%entity", sgd_DestroyEntity);
	rtSym("%CopyEntity%entity", sgd_CopyEntity);
	rtSym("SetEntityParent%entity%parent", sgd_SetEntityParent);
	rtSym("%EntityParent%entity", sgd_EntityParent);
	rtSym("SetEntityPosition%entity#x#y#z", sgd_SetEntityPosition);
	rtSym("SetEntityRotation%entity#rx#ry#rz", sgd_SetEntityRotation);
	rtSym("SetEntityScale%entity#sx#sy#sz", sgd_SetEntityScale);
	rtSym("TranslateEntity%entity#x#y#z", sgd_TranslateEntity);
	rtSym("RotateEntity%entity#rx#ry#rz", sgd_RotateEntity);
	rtSym("ScaleEntity%entity#sx#sy#sz", sgd_ScaleEntity);
	rtSym("MoveEntity%entity#x#y#z", sgd_MoveEntity);
	rtSym("TurnEntity%entity#rx#ry#rz", sgd_TurnEntity);
	rtSym("#EntityX%entity", sgd_EntityX);
	rtSym("#EntityY%entity", sgd_EntityY);
	rtSym("#EntityZ%entity", sgd_EntityZ);
	rtSym("#EntityRX%entity", sgd_EntityRX);
	rtSym("#EntityRY%entity", sgd_EntityRY);
	rtSym("#EntityRZ%entity", sgd_EntityRZ);
	rtSym("#EntitySX%entity", sgd_EntitySX);
	rtSym("#EntitySY%entity", sgd_EntitySY);
	rtSym("#EntitySZ%entity", sgd_EntitySZ);
	rtSym("AimEntityAtEntity%entity%target#roll", sgd_AimEntityAtEntity);
	rtSym("AimEntityAtPoint%entity#x#y#z#roll", sgd_AimEntityAtPoint);
	rtSym("TFormPoint#x#y#z%srcEntity%dstEntity", sgd_TFormPoint);
	rtSym("TFormVector#x#y#z%srcEntity%dstEntity", sgd_TFormVector);
	rtSym("TFormNormal#x#y#z%srcEntity%dstEntity", sgd_TFormNormal);
	rtSym("#TFormedX", sgd_TFormedX);
	rtSym("#TFormedY", sgd_TFormedY);
	rtSym("#TFormedZ", sgd_TFormedZ);

	// Camera
	rtSym("%CreatePerspectiveCamera", sgd_CreatePerspectiveCamera);
	rtSym("%CreateOrthographicCamera", sgd_CreateOrthographicCamera);
	rtSym("SetCameraFOV%camera#fov", sgd_SetCameraFOV);
	rtSym("SetCameraNear%camera#near", sgd_SetCameraNear);
	rtSym("SetCameraFar%camera#far", sgd_SetCameraFar);
	rtSym("%CameraProject%camera#x#y#z", sgd_CameraProject);
	rtSym("#ProjectedX", sgd_ProjectedX);
	rtSym("#ProjectedY", sgd_ProjectedY);

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
	rtSym("SetLightPriority%light%priority", sgd_SetLightPriority);
	rtSym("LightCastsShadow%light", sgd_LightCastsShadow);

	// Model
	rtSym("%LoadModel$path", loadModel);
	rtSym("%LoadBonedModel$path%skinned", loadBonedModel);
	rtSym("%CreateModel%mesh", sgd_CreateModel);
	rtSym("SetModelMesh%model%mesh", sgd_SetModelMesh);
	rtSym("%ModelMesh%model", sgd_ModelMesh);
	rtSym("SetModelColor%model#red#green#blue#alpha", sgd_SetModelColor);
	rtSym("AnimateModel%model%animation#time%mode#weight", sgd_AnimateModel);

	// Skybox
	rtSym("%LoadSkybox$path#roughness", loadSkybox);
	rtSym("%CreateSkybox%texture", sgd_CreateSkybox);
	rtSym("SetSkyboxTexture%skybox%texture", sgd_SetSkyboxTexture);
	rtSym("SetSkyboxRoughness%skybox#roughness", sgd_SetSkyboxRoughness);

	// Sprite
	rtSym("%CreateSprite%image", sgd_CreateSprite);
	rtSym("SetSpriteImage%sprite%image", sgd_SetSpriteImage);
	rtSym("SetSpriteColor%sprite#red#green#blue#alpha", sgd_SetSpriteColor);
	rtSym("SetSpriteFrame%sprite#frame", sgd_SetSpriteFrame);

	// Collisions
	rtSym("%CreateSphereCollider%entity%colliderType#radius", sgd_CreateSphereCollider);
	rtSym("%CreateEllipsoidCollider%entity%colliderType#radius#height", sgd_CreateEllipsoidCollider);
	rtSym("%CreateMeshCollider%entity%colliderType%mesh", sgd_CreateMeshCollider);
	rtSym("SetColliderRadius%collider#radius", sgd_SetColliderRadius);
	rtSym("SetColliderHeight%collider#height", sgd_SetColliderHeight);
	rtSym("EnableCollisions%srcColliderType%dstColliderType%collisionResponse", sgd_EnableCollisions);
	rtSym("UpdateColliders", sgd_UpdateColliders);
	rtSym("%CameraPick%camera#windowX#windowY%colliderMask", sgd_CameraPick);
	rtSym("%LinePick#x0#y0#z0#x1#y1#z1#radius%colliderMask", sgd_LinePick);
	rtSym("#PickedX", sgd_PickedX);
	rtSym("#PickedY", sgd_PickedY);
	rtSym("#PickedZ", sgd_PickedZ);
	rtSym("#PickedNX", sgd_PickedNX);
	rtSym("#PickedNY", sgd_PickedNY);
	rtSym("#PickedNZ", sgd_PickedNZ);

	return true;
}
