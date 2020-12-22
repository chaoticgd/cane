#pragma once

#include <glm/mat4x4.hpp>
#include <Renderer/Camera.h>
#include <Gui/RenderBuffer.h>
#include <Utility/Config.h>
#include <vector>

class SlyMesh;
class Editor;
class Thumbnail;
class ModelBrowser : public TexturedRenderBuffer {
public:
	ModelBrowser() {
		resize_buffer(width, height); 
		calculate_projection_matrix();
	}

	void render();
	void make_thumbnails();

	glm::mat4& projection() { if (m_should_recalculate_projection) calculate_projection_matrix(); return m_projection; };
	Camera& camera() { return m_camera; }

private:
	void calculate_projection_matrix() {
		//TODO new fov? idk
		m_projection = glm::perspective(config::the().renderer.fov, (float)width / (float)height, 0.1f, 250.0f);
	}

	Camera m_camera{};
	glm::mat4 m_projection{ 1.0f };

	const int width = 1024;
	const int height = 1024;

	std::vector<Thumbnail> m_thumbnails;

	bool m_should_recalculate_projection{ true };

};

class Thumbnail : public TexturedRenderBuffer {
public:
	Thumbnail(int index_into_buffer) : m_index_into_buffer(index_into_buffer) { resize_buffer(128, 128); }

	void render(SlyMesh& mesh);
	const int index() const { return m_index_into_buffer; }

private:
	int m_index_into_buffer;
};