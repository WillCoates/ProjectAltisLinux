from __future__ import absolute_import
#import urlparse as _urlparse
# Altis urlparse is broken (list() takes at most 1 argument (5 given))
from altispatch import urlparse as _urlparse


def register_scheme(scheme):
    for method in filter(lambda s: s.startswith('uses_'), dir(_urlparse)):
        uses = getattr(_urlparse, method)
        if scheme not in uses:
            uses.append(scheme)


urlparse = _urlparse.urlparse
