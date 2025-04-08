uniform sampler2D texture;

uniform float t;
uniform vec2 r;

void main()
{
    // lookup the pixel in the texture
    vec4 p = texture2D(texture, gl_TexCoord[0].xy);

	vec3 c;
	float l,z=t;
	for(int i=0;i<3;i++) {
		vec2 uv,p=gl_FragCoord.xy/r;
		uv=p;
		p-=.5;
		p.x*=r.x/r.y;
		z+=.07;
		l=length(p);
		uv+=p/l*(sin(z)+1.)*abs(sin(l*9.-z-z));
		c[i]=.01/length(mod(uv,1.)-.5);
	}


    // multiply it by the color
    gl_FragColor = vec4(c/l,t);
}