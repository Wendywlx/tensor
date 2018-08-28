#include <matazure/tensor>

using namespace matazure;

template <typename _Tensor>
auto split(_Tensor ts) {
	return make_lambda(pointi<3>{ts.shape()[0], ts.shape()[1], 3}, [ts](pointi<3> idx) {
		auto bgr = ts(pointi<2>{idx[0], idx[1]});
		return bgr[idx[2]];
	});
}

int main() {
	tensor<point<byte, 3>, 2> ts_bgr(pointi<2>{256, 256});
	point<byte, 3> mean{ 110, 107, 125 };
	point<float, 3> scale{ 0.125f, 0.125f, 0.125f };
	auto lts_bgr_normalize = cast<point<float, 3>>(ts_bgr - mean) * scale;
	auto lts_plane = split(lts_bgr_normalize);
	auto ts_plane = lts_plane.persist();

	return 0;
}
