#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _TextureSource; //CurrentTexture
uniform sampler2D _TextureEffect;

void main()
{
	gl_FragColor = texture2D(_TextureSource, gl_TexCoord[0].xy) * 0.5 + texture2D(_TextureEffect, gl_TexCoord[0].xy) * 0.5;
}

