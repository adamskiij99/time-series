# -*- coding: utf-8 -*-
"""
Created on Mon Oct 24 16:37:18 2022

@author: Administrator
"""

import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt
import os
os.chdir("time series")

# %%
series = genfromtxt("AR.csv", delimiter = ",")
title = "Autoregressive Model"
# %%
series = genfromtxt("MA.csv", delimiter = ",")
title = "Moving Average Model"
# %%
series = genfromtxt("ARMA.csv", delimiter = ",")
title = "Autoregressive Moving Average"
# %%
series = genfromtxt("ARIMA.csv", delimiter = ",")
title = "Autoregressive Integrated Moving Average"
# %%
series = genfromtxt("ARCH.csv", delimiter = ",")
title = "Autoregressive Conditional Heteroskedasticity"
# %%
series = genfromtxt("GARCH.csv", delimiter = ",")
title = "Generalised Autoregressive Conditional Heteroskedasticity"
#%%

fig = plt.figure(figsize = (12, 4), dpi = 160)
plt.style.use("bmh")
plt.title(title)
plt.fill_between(np.arange(len(series)), series)
plt.show()


