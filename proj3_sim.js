/*
 * Global variables
 */
var meshResolution;

// Particle states
var mass;
var vertexPosition, vertexNormal;
var vertexVelocity;

// Spring properties
var K, restLength; 

// Force parameters
var Cd;
var uf, Cv;


/*
 * Getters and setters
 */
function getPosition(i, j) {
    var id = i*meshResolution + j;
    return vec3.create([vertexPosition[3*id], vertexPosition[3*id + 1], vertexPosition[3*id + 2]]);
}

function setPosition(i, j, x) {
    var id = i*meshResolution + j;
    vertexPosition[3*id] = x[0]; vertexPosition[3*id + 1] = x[1]; vertexPosition[3*id + 2] = x[2];
}

function getNormal(i, j) {
    var id = i*meshResolution + j;
    return vec3.create([vertexNormal[3*id], vertexNormal[3*id + 1], vertexNormal[3*id + 2]]);
}

function getVelocity(i, j) {
    var id = i*meshResolution + j;
    return vec3.create(vertexVelocity[id]);
}

function setVelocity(i, j, v) {
    var id = i*meshResolution + j;
    vertexVelocity[id] = vec3.create(v);
}


/*
 * Provided global functions (you do NOT have to modify them)
 */
function computeNormals() {
    var dx = [1, 1, 0, -1, -1, 0], dy = [0, 1, 1, 0, -1, -1];
    var e1, e2;
    var i, j, k = 0, t;
    for ( i = 0; i < meshResolution; ++i )
        for ( j = 0; j < meshResolution; ++j ) {
            var p0 = getPosition(i, j), norms = [];
            for ( t = 0; t < 6; ++t ) {
                var i1 = i + dy[t], j1 = j + dx[t];
                var i2 = i + dy[(t + 1) % 6], j2 = j + dx[(t + 1) % 6];
                if ( i1 >= 0 && i1 < meshResolution && j1 >= 0 && j1 < meshResolution &&
                     i2 >= 0 && i2 < meshResolution && j2 >= 0 && j2 < meshResolution ) {
                    e1 = vec3.subtract(getPosition(i1, j1), p0);
                    e2 = vec3.subtract(getPosition(i2, j2), p0);
                    norms.push(vec3.normalize(vec3.cross(e1, e2)));
                }
            }
            e1 = vec3.create();
            for ( t = 0; t < norms.length; ++t ) vec3.add(e1, norms[t]);
            vec3.normalize(e1);
            vertexNormal[3*k] = e1[0];
            vertexNormal[3*k + 1] = e1[1];
            vertexNormal[3*k + 2] = e1[2];
            ++k;
        }
}


var clothIndex, clothWireIndex;
function initMesh() {
    var i, j, k;

    vertexPosition = new Array(meshResolution*meshResolution*3);
    vertexNormal = new Array(meshResolution*meshResolution*3);
    clothIndex = new Array((meshResolution - 1)*(meshResolution - 1)*6);
    clothWireIndex = [];

    vertexVelocity = new Array(meshResolution*meshResolution);
    restLength[0] = 4.0/(meshResolution - 1);
    restLength[1] = Math.sqrt(2.0)*4.0/(meshResolution - 1);
    restLength[2] = 2.0*restLength[0];

    for ( i = 0; i < meshResolution; ++i )
        for ( j = 0; j < meshResolution; ++j ) {
            setPosition(i, j, [-2.0 + 4.0*j/(meshResolution - 1), -2.0 + 4.0*i/(meshResolution - 1), 0.0]);
            setVelocity(i, j, vec3.create());

            if ( j < meshResolution - 1 )
                clothWireIndex.push(i*meshResolution + j, i*meshResolution + j + 1);
            if ( i < meshResolution - 1 )
                clothWireIndex.push(i*meshResolution + j, (i + 1)*meshResolution + j);
            if ( i < meshResolution - 1 && j < meshResolution - 1 )
                clothWireIndex.push(i*meshResolution + j, (i + 1)*meshResolution + j + 1);
        }
    computeNormals();

    k = 0;
    for ( i = 0; i < meshResolution - 1; ++i )
        for ( j = 0; j < meshResolution - 1; ++j ) {
            clothIndex[6*k] = i*meshResolution + j;
            clothIndex[6*k + 1] = i*meshResolution + j + 1;
            clothIndex[6*k + 2] = (i + 1)*meshResolution + j + 1;
            clothIndex[6*k + 3] = i*meshResolution + j;
            clothIndex[6*k + 4] = (i + 1)*meshResolution + j + 1;            
            clothIndex[6*k + 5] = (i + 1)*meshResolution + j;
            ++k;
        }
}

printed = false

function divide(vector, value) {
    vector[0] = vector[0]/value
    vector[1] = vector[1]/value
    vector[2] = vector[2]/value

    return vector
}

function multiply(vector, value) {
    vector[0] = vector[0] * value
    vector[1] = vector[1] * value
    vector[2] = vector[2] * value

    return vector
}


//p and q are positions (vec3s)
function calculateSpring(p, q, K_i, restLength_i) {
    x_dist = p[0] - q[0]
    y_dist = p[1] - q[1]
    z_dist = p[2] - q[2]
    distance = Math.sqrt((x_dist * x_dist) + (y_dist * y_dist) + (z_dist * z_dist))
    return multiply(vec3.normalize(vec3.subtract(vec3.create(p), q)), K_i * (restLength_i - distance))
}

function isValid(i, j) {
    return i >= 0 && i < meshResolution && j >= 0 && j<meshResolution
}

function isPinned(i, j) {
    return (i == meshResolution - 1 && j == 0) || (i == meshResolution - 1 && j == meshResolution - 1)
}

function add(vec1, vec2) {
    return vec3.create([vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z])
}


/*
 * KEY function: simulate one time-step using Euler's method
 */
function simulate(stepSize) {
    // FIX ME
    //for each particle....
    for ( i = 0; i < meshResolution; ++i) {
        for ( j = 0; j < meshResolution; ++j) {
            // Compute the accumulated force Fi,j acting on each particle 
                v = getVelocity(i, j)
                n = getNormal(i, j)
                x = getPosition(i, j)
                f_spring = vec3.create(0,0,0)

                /** STRUCTURAL SPRING FORCES **/
                if(isValid(i, j+1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i, j+1), K[0], restLength[0]));
                }
                if(isValid(i, j-1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i, j-1), K[0], restLength[0]));
                }
                if(isValid(i+1, j)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i+1, j), K[0], restLength[0]));
                }
                if(isValid(i-1, j)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i-1, j), K[0], restLength[0]));
                }
                /** SHEAR SPRING FORCES **/
                if(isValid(i+1, j+1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i+1, j+1), K[1], restLength[1]));
                }
                if(isValid(i+1, j-1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i+1, j-1), K[1], restLength[1]));
                }
                if(isValid(i-1, j-1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i-1, j-1), K[1], restLength[1]));
                }
                if(isValid(i-1, j+1)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i-1, j+1), K[1], restLength[1]));
                }
                /** FLEXION (BEND) SPRING FORCES **/
                if(isValid(i, j+2)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i, j+2), K[2], restLength[2]));
                }
                if(isValid(i, j-2)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i, j-2), K[2], restLength[2]));
                }
                if(isValid(i+2, j)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i+2, j), K[2], restLength[2]));
                }
                if(isValid(i-2, j)) {
                    vec3.add(f_spring, calculateSpring(x, getPosition(i-2, j), K[2], restLength[2]));
                }

                f_gravity = vec3.create([0, -1 * mass * 9.8 , 0]);
                f_damping = multiply(v, -1 * Cd);
                f_viscous =  multiply(n, Cv * vec3.dot(n, (vec3.subtract(vec3.create(uf), v))));

                F = vec3.create(0,0,0);
                
                vec3.add(F, f_spring)
                vec3.add(F, f_gravity)
                vec3.add(F, f_damping)
                vec3.add(F,f_viscous);

                vec3.add(v, multiply(divide(F,mass), stepSize));
                setVelocity(i, j, v);
                vec3.add(x, multiply(v, stepSize));
                if(!isPinned(i, j)) {
                    setPosition(i, j, x);
                }
        }
    }
    computeNormals()
}