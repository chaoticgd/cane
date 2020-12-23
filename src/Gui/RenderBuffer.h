#pragma once

typedef unsigned int GLuint;

class TexturedRenderBuffer {
public:
	TexturedRenderBuffer() {}
	TexturedRenderBuffer(TexturedRenderBuffer&& buffer) noexcept :
		m_fbo(buffer.m_fbo), m_depthbuffer(buffer.m_depthbuffer), m_texture(buffer.m_texture)
	{
		buffer.m_allocated = false;
	}
	TexturedRenderBuffer(const TexturedRenderBuffer&) = delete;
	virtual ~TexturedRenderBuffer() {
		free_buffer();
	}

	void free_buffer();
	void resize_buffer(int width, int height);
	const bool is_allocated() const { return m_allocated; }
	const GLuint fbo() const { return m_fbo; }
	const GLuint depth_buffer() const { return m_depthbuffer; }
	const GLuint texture() const { return m_texture; }

private:
	GLuint m_fbo{ 0 }, m_depthbuffer{ 0 }, m_texture{ 0 };
	bool m_allocated{false};
};