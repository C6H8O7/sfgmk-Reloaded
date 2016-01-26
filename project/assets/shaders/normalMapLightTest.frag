#ifdef GL_ES
precision mediump float;
#endif


uniform sampler2D _TextureSource; //CurrentTexture
uniform vec2 _MousePos; //MousePosition
uniform vec3 _LightPos;
uniform float _LightRange;
uniform vec4 _LightColor; //Color
uniform float _LightPower;

void main()
{
	vec4 TexColor = texture2D(_TextureSource, gl_TexCoord[0].xy);
	vec3 NormalVector = TexColor.xyz;
	NormalVector.xy += vec2(-0.5, -0.5); //Normal maps add 0.5 to avoid negative values (can't set negative values in textures)
	
	vec3 LightDirection = vec3(_MousePos.xy - gl_FragCoord.xy, _LightPos.z);
	float LightRatio = 1.0 - (distance(gl_FragCoord.xy, _MousePos.xy) / _LightRange);
	
	NormalVector = normalize(NormalVector);
	LightDirection = normalize(LightDirection);
	
	float diffuse = _LightPower * max(dot( NormalVector, LightDirection ), 0.0); //Dot can give values between -1 and 1, use max to avoid negatives
	
	gl_FragColor = vec4(_LightColor.rgb * diffuse * LightRatio, TexColor.a);
}