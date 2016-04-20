uniform sampler2D _currentTexture;

const float blurSize = 1.0 / 512.0;
const float intensity = 0.3;

void main()
{
   vec4 sum = vec4(0);
   vec2 texcoord = gl_TexCoord[0].xy;

   //thank you! http://www.gamerendering.com/2008/10/11/gaussian-blur-filter-shader/ for the 
   //blur tutorial
   // blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(_currentTexture, vec2(texcoord.x - 4.0*blurSize, texcoord.y)) * 0.05;
   sum += texture2D(_currentTexture, vec2(texcoord.x - 3.0*blurSize, texcoord.y)) * 0.09;
   sum += texture2D(_currentTexture, vec2(texcoord.x - 2.0*blurSize, texcoord.y)) * 0.12;
   sum += texture2D(_currentTexture, vec2(texcoord.x - blurSize, texcoord.y)) * 0.15;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y)) * 0.16;
   sum += texture2D(_currentTexture, vec2(texcoord.x + blurSize, texcoord.y)) * 0.15;
   sum += texture2D(_currentTexture, vec2(texcoord.x + 2.0*blurSize, texcoord.y)) * 0.12;
   sum += texture2D(_currentTexture, vec2(texcoord.x + 3.0*blurSize, texcoord.y)) * 0.09;
   sum += texture2D(_currentTexture, vec2(texcoord.x + 4.0*blurSize, texcoord.y)) * 0.05;
	
	// blur in y (vertical)
   // take nine samples, with the distance blurSize between them
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y - blurSize)) * 0.15;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y)) * 0.16;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y + blurSize)) * 0.15;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(_currentTexture, vec2(texcoord.x, texcoord.y + 4.0*blurSize)) * 0.05;

   //increase blur with intensity!
   gl_FragColor = sum * intensity + texture2D(_currentTexture, texcoord); 
}