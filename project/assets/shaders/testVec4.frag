#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _CurrentTexture; //CurrentTexture
uniform vec4 _Test;

void main()
{
	gl_FragColor = _Test;
}