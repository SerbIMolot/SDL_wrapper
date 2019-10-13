#pragma once

#include "stdafx.h"

static GPU_Target* Init(GPU_Renderer* renderer, GPU_RendererID renderer_request, Uint16 w, Uint16 h, GPU_WindowFlagEnum SDL_flags);

static GPU_Target* CreateTargetFromWindow(GPU_Renderer* renderer, Uint32 windowID, GPU_Target* target);

static GPU_Target* CreateAliasTarget(GPU_Renderer* renderer, GPU_Target* target);

static void MakeCurrent(GPU_Renderer* renderer, GPU_Target* target, Uint32 windowID);

static void SetAsCurrent(GPU_Renderer* renderer);

static GPU_bool SetActiveTarget(GPU_Renderer* renderer, GPU_Target* target);

static void ResetRendererState(GPU_Renderer* renderer);

static GPU_bool AddDepthBuffer(GPU_Renderer* renderer, GPU_Target* target);

static GPU_bool SetWindowResolution(GPU_Renderer* renderer, Uint16 w, Uint16 h);

static void SetVirtualResolution(GPU_Renderer* renderer, GPU_Target* target, Uint16 w, Uint16 h);

static void UnsetVirtualResolution(GPU_Renderer* renderer, GPU_Target* target);

static void Quit(GPU_Renderer* renderer);

static GPU_bool SetFullscreen(GPU_Renderer* renderer, GPU_bool enable_fullscreen, GPU_bool use_desktop_resolution);

static GPU_Camera SetCamera(GPU_Renderer* renderer, GPU_Target* target, GPU_Camera* cam);

static GPU_Image* CreateImage(GPU_Renderer* renderer, Uint16 w, Uint16 h, GPU_FormatEnum format);

static GPU_Image* CreateImageUsingTexture(GPU_Renderer* renderer, GPU_TextureHandle handle, GPU_bool take_ownership);

static GPU_Image* CreateAliasImage(GPU_Renderer* renderer, GPU_Image* image);

static GPU_bool SaveImage(GPU_Renderer* renderer, GPU_Image* image, const char* filename, GPU_FileFormatEnum format);

static GPU_Image* CopyImage(GPU_Renderer* renderer, GPU_Image* image);

static void UpdateImage(GPU_Renderer* renderer, GPU_Image* image, const GPU_Rect* image_rect, SDL_Surface* surface, const GPU_Rect* surface_rect);

static void UpdateImageBytes(GPU_Renderer* renderer, GPU_Image* image, const GPU_Rect* image_rect, const unsigned char* bytes, int bytes_per_row);

static GPU_bool ReplaceImage(GPU_Renderer* renderer, GPU_Image* image, SDL_Surface* surface, const GPU_Rect* surface_rect);

static GPU_Image* CopyImageFromSurface(GPU_Renderer* renderer, SDL_Surface* surface);

static GPU_Image* CopyImageFromTarget(GPU_Renderer* renderer, GPU_Target* target);

static SDL_Surface* CopySurfaceFromTarget(GPU_Renderer* renderer, GPU_Target* target);

static SDL_Surface* CopySurfaceFromImage(GPU_Renderer* renderer, GPU_Image* image);

static void FreeImage(GPU_Renderer* renderer, GPU_Image* image);

static GPU_Target* GetTarget(GPU_Renderer* renderer, GPU_Image* image);

static void FreeTarget(GPU_Renderer* renderer, GPU_Target* target);

static void Blit(GPU_Renderer* renderer, GPU_Image* image, GPU_Rect* src_rect, GPU_Target* target, float x, float y);

static void BlitRotate(GPU_Renderer* renderer, GPU_Image* image, GPU_Rect* src_rect, GPU_Target* target, float x, float y, float degrees);

static void BlitScale(GPU_Renderer* renderer, GPU_Image* image, GPU_Rect* src_rect, GPU_Target* target, float x, float y, float scaleX, float scaleY);

static void BlitTransform(GPU_Renderer* renderer, GPU_Image* image, GPU_Rect* src_rect, GPU_Target* target, float x, float y, float degrees, float scaleX, float scaleY);

static void BlitTransformX(GPU_Renderer* renderer, GPU_Image* image, GPU_Rect* src_rect, GPU_Target* target, float x, float y, float pivot_x, float pivot_y, float degrees, float scaleX, float scaleY);

static void PrimitiveBatchV(GPU_Renderer* renderer, GPU_Image* image, GPU_Target* target, GPU_PrimitiveEnum primitive_type, unsigned short num_vertices, void* values, unsigned int num_indices, unsigned short* indices, GPU_BatchFlagEnum flags);

static void GenerateMipmaps(GPU_Renderer* renderer, GPU_Image* image);

static GPU_Rect SetClip(GPU_Renderer* renderer, GPU_Target* target, Sint16 x, Sint16 y, Uint16 w, Uint16 h);

static void UnsetClip(GPU_Renderer* renderer, GPU_Target* target);

static SDL_Color GetPixel(GPU_Renderer* renderer, GPU_Target* target, Sint16 x, Sint16 y);

static void SetImageFilter(GPU_Renderer* renderer, GPU_Image* image, GPU_FilterEnum filter);

static void SetWrapMode(GPU_Renderer* renderer, GPU_Image* image, GPU_WrapEnum wrap_mode_x, GPU_WrapEnum wrap_mode_y);

static GPU_TextureHandle GetTextureHandle(GPU_Renderer* renderer, GPU_Image* image);

static void ClearRGBA(GPU_Renderer* renderer, GPU_Target* target, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

static void FlushBlitBuffer(GPU_Renderer* renderer);

static void Flip(GPU_Renderer* renderer, GPU_Target* target);

static Uint32 CreateShaderProgram(GPU_Renderer* renderer);

static void FreeShaderProgram(GPU_Renderer* renderer, Uint32 program_object);

static Uint32 CompileShader_RW(GPU_Renderer* renderer, GPU_ShaderEnum shader_type, SDL_RWops* shader_source, GPU_bool free_rwops);

static Uint32 CompileShader(GPU_Renderer* renderer, GPU_ShaderEnum shader_type, const char* shader_source);

static void FreeShader(GPU_Renderer* renderer, Uint32 shader_object);

static void AttachShader(GPU_Renderer* renderer, Uint32 program_object, Uint32 shader_object);

static void DetachShader(GPU_Renderer* renderer, Uint32 program_object, Uint32 shader_object);

static GPU_bool LinkShaderProgram(GPU_Renderer* renderer, Uint32 program_object);

static void ActivateShaderProgram(GPU_Renderer* renderer, Uint32 program_object, GPU_ShaderBlock* block);

static void DeactivateShaderProgram(GPU_Renderer* renderer);

static const char* GetShaderMessage(GPU_Renderer* renderer);

static int GetAttributeLocation(GPU_Renderer* renderer, Uint32 program_object, const char* attrib_name);

static int GetUniformLocation(GPU_Renderer* renderer, Uint32 program_object, const char* uniform_name);

static GPU_ShaderBlock LoadShaderBlock(GPU_Renderer* renderer, Uint32 program_object, const char* position_name, const char* texcoord_name, const char* color_name, const char* modelViewMatrix_name);

static void SetShaderImage(GPU_Renderer* renderer, GPU_Image* image, int location, int image_unit);

static void GetUniformiv(GPU_Renderer* renderer, Uint32 program_object, int location, int* values);

static void SetUniformi(GPU_Renderer* renderer, int location, int value);

static void SetUniformiv(GPU_Renderer* renderer, int location, int num_elements_per_value, int num_values, int* values);

static void GetUniformuiv(GPU_Renderer* renderer, Uint32 program_object, int location, unsigned int* values);

static void SetUniformui(GPU_Renderer* renderer, int location, unsigned int value);

static void SetUniformuiv(GPU_Renderer* renderer, int location, int num_elements_per_value, int num_values, unsigned int* values);

static void GetUniformfv(GPU_Renderer* renderer, Uint32 program_object, int location, float* values);

static void SetUniformf(GPU_Renderer* renderer, int location, float value);

static void SetUniformfv(GPU_Renderer* renderer, int location, int num_elements_per_value, int num_values, float* values);

static void SetUniformMatrixfv(GPU_Renderer* renderer, int location, int num_matrices, int num_rows, int num_columns, GPU_bool transpose, float* values);

static void SetAttributef(GPU_Renderer* renderer, int location, float value);

static void SetAttributei(GPU_Renderer* renderer, int location, int value);

static void SetAttributeui(GPU_Renderer* renderer, int location, unsigned int value);

static void SetAttributefv(GPU_Renderer* renderer, int location, int num_elements, float* value);

static void SetAttributeiv(GPU_Renderer* renderer, int location, int num_elements, int* value);

static void SetAttributeuiv(GPU_Renderer* renderer, int location, int num_elements, unsigned int* value);

static void SetAttributeSource(GPU_Renderer* renderer, int num_values, GPU_Attribute source);

static float SetLineThickness(GPU_Renderer* renderer, float thickness);

static float GetLineThickness(GPU_Renderer* renderer);

static void Pixel(GPU_Renderer* renderer, GPU_Target* target, float x, float y, SDL_Color color);

static void Line(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color);

static void Arc(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float radius, float start_angle, float end_angle, SDL_Color color);

static void ArcFilled(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float radius, float start_angle, float end_angle, SDL_Color color);

static void Circle(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float radius, SDL_Color color);

static void CircleFilled(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float radius, SDL_Color color);

static void Ellipse(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float rx, float ry, float degrees, SDL_Color color);

static void EllipseFilled(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float rx, float ry, float degrees, SDL_Color color);

static void Sector(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float inner_radius, float outer_radius, float start_angle, float end_angle, SDL_Color color);

static void SectorFilled(GPU_Renderer* renderer, GPU_Target* target, float x, float y, float inner_radius, float outer_radius, float start_angle, float end_angle, SDL_Color color);

static void Tri(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);

static void TriFilled(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, float x3, float y3, SDL_Color color);

static void Rectangle(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color);

static void RectangleFilled(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, SDL_Color color);

static void RectangleRound(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, float radius, SDL_Color color);

static void RectangleRoundFilled(GPU_Renderer* renderer, GPU_Target* target, float x1, float y1, float x2, float y2, float radius, SDL_Color color);

static void Polygon(GPU_Renderer* renderer, GPU_Target* target, unsigned int num_vertices, float* vertices, SDL_Color color);

static void PolygonFilled(GPU_Renderer* renderer, GPU_Target* target, unsigned int num_vertices, float* vertices, SDL_Color color);

void set_renderer_functions(GPU_RendererImpl* impl);

GPU_Renderer* create_dummy_renderer(GPU_RendererID request);

void free_dummy_renderer(GPU_Renderer* renderer);
