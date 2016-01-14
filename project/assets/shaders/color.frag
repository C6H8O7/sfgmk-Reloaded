#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _TextureSource; //CurrentTexture
uniform vec4 _Color; //Color

void main()
{
	gl_FragColor = _Color;
}

