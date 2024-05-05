#include <libzork/store/store.hh>
#include <memory>

#include "exceptions.hh"
#include "store/store_impl.hh"

namespace libzork::store
{

    std::unique_ptr<Store> make_store()
    {
        return std::make_unique<StoreImpl>(StoreImpl());
    }

} // namespace libzork::store
