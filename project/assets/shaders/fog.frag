#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _TextureSource; //CurrentTexture
uniform vec4 _FogColor; //Color
uniform vec2 _MousePos; //MousePosition
uniform float _DistanceMax;

float CalcFog()
{
	vec2 Direction = gl_FragCoord.xy - _MousePos.xy;
	
    return (Direction.x * Direction.x + Direction.y * Direction.y) / _DistanceMax;
}

void main()
{
	//Ratio function of distance
	float fRatio = CalcFog();
	
    //Combine image and fog color
	gl_FragColor = texture2D(_TextureSource, gl_TexCoord[0].xy) * (1.0 - fRatio)  + _FogColor * fRatio;
}

