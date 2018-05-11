#include "../include/Rect.h"
#include "../include/Vec2.h"

#include <algorithm>
#include <cmath>

class Collision {

	public:
		// Observação: IsColliding espera ângulos em radianos!
		// Para usar graus, forneça a sua própria implementação de Rotate,
		// ou transforme os ângulos no corpo de IsColliding.
		static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
			Vec2 A[] = { Vec2( a.x, a.y + a.h ),
						  Vec2( a.x + a.w, a.y + a.h ),
						  Vec2( a.x + a.w, a.y ),
						  Vec2( a.x, a.y )
						};
			Vec2 B[] = { Vec2( b.x, b.y + b.h ),
						  Vec2( b.x + b.w, b.y + b.h ),
						  Vec2( b.x + b.w, b.y ),
						  Vec2( b.x, b.y )
						};

            Vec2 aCenter = a.Center(a);
            Vec2 bCenter = b.Center(b);


			for (auto& v : A) {
                v = v.SubVectors(v,aCenter);
                v.GetRotated(angleOfA);
                v = v.AddVectors(v,aCenter);
				//v = Rotate(v - a.Center(a), angleOfA) + a.Center(a);
			}

			for (auto& v : B) {
                v = v.SubVectors(v,bCenter);
                v.GetRotated(angleOfB);
                v = v.AddVectors(v,bCenter);
				//v = Rotate(v - b.Center(b), angleOfB) + b.Center(b);
			}
            Vec2 A1 = A1.SubVectors(A[0],A[1]);
            A1.NormalizeVec(&A1);
            Vec2 A2 = A2.SubVectors(A[1],A[2]);
            A2.NormalizeVec(&A2);

            Vec2 B1 = B1.SubVectors(B[0],B[1]);
            B1.NormalizeVec(&B1);
            Vec2 B2 = B2.SubVectors(B[1],B[2]);
            B2.NormalizeVec(&B2);

                        
			Vec2 axes[] = { A1,
                            A2, 
                            B1, 
                            B2 };

			for (auto& axis : axes) {
				float P[4];

				for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

				float minA = *std::min_element(P, P + 4);
				float maxA = *std::max_element(P, P + 4);

				for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

				float minB = *std::min_element(P, P + 4);
				float maxB = *std::max_element(P, P + 4);

				if (maxA < minB || minA > maxB)
					return false;
			}

			return true;
		}

	private:
		static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x * b.x + a.y * b.y;
		}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }