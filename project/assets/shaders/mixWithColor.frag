#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _TextureSource; //CurrentTexture
uniform vec4 _Color; //Color

void main()
{
	gl_FragColor = texture2D(_TextureSource, gl_TexCoord[0].xy) * 0.5 + _Color * 0.5;
}

