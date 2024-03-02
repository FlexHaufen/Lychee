#include <Lychee/Lychee.h>

#include "RuntimeLayer.h"

namespace Lychee {

	class LycheeRuntime : public Core {
	public:
		LycheeRuntime()
			: Core() {
            
			LY_INFO("Starting Lychee Runtime");
			PushLayer(new RuntimeLayer());
		}   
	};
}
