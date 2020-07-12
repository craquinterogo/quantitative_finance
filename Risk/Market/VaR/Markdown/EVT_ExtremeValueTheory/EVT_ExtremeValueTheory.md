```python
import pandas as pd
import numpy as np
import datetime
import matplotlib.pyplot as plt
from scipy.stats import genpareto, norm
import math
```


```python
np.warnings.filterwarnings('ignore')
```

# Objective

The aim of this work is to take an insight on the VaR (Value at Risk) approach using EVT (Extreme Value Theory). This is used as an approach to take into account an issue which anothers approachs don't take into account, and with this I mean fat tails. Fat tails do contain valuable information, specially in asset's returns. In fat tails risk managers can get a measure which let them calculate a most realistic level where the biggest losse is possible within a confidence level.

Some basic VaR forms, as theoretical parametrical VaR, take a view of asset's returns as a random variable wich is described by a normal distribution, and with this all assumptions this could have. For example normal distribution doesn't have fat tails, and with this the model consider exceptional cases with lower frequency. Market asset's returns don't have this behaviour.

# Data Reading

To complete this goal, we get data of American Express (AXP) close prices from 4-Jan-2011 to 3-Jan-2020. The selection of this stock was random, and no was an output of rigurous study of stocks behaviour. The data was retrieved of <a href='https://www.investing.com/equities/american-express'>Investing.com</a> webpage.


```python
prices = pd.read_csv('datasource/AXP Historical Data.csv')
```


```python
prices['Date'] = prices['Date'].apply(lambda x: datetime.datetime.strptime(x,'%b %d, %Y'))
prices.sort_values(['Date'], inplace=True)
prices['Date'] = prices['Date'].dt.to_period('D')
prices.set_index('Date', inplace=True)
```


```python
prices['return'] = prices['Price'].pct_change() * 100
```

# American Express returns histogram


```python
plt.figure(figsize=(15,7))
plt.hist(prices['return'], bins=100)
plt.title(
    'American Express Stock Returns Histogram : '+
    min(prices.index).strftime('%Y-%m-%d')+
    ' to '+
    max(prices.index).strftime('%Y-%m-%d'),
    fontsize=17
)
plt.xlabel('Return (%)')
plt.ylabel('Frequency')
plt.show()
```


![png](output_10_0.png)



```python
print('Mean\t\t : ',prices['return'].mean())
print('Variance\t : ',prices['return'].var())
print('Skewness\t : ',prices['return'].skew())
print('Kurtosis\t : ',prices['return'].kurtosis())
```

    Mean		 :  0.05507091359887325
    Variance	 :  1.8006052702755442
    Skewness	 :  -0.3857569777177754
    Kurtosis	 :  7.120513770330035


Is clear with histogram above, the American Express returns don't be described by normal distribution, because it has kurtosis equal to 7.12 (normal distribution has kurtosis = 3), although it has lowest negative skewness of -0.38. In many textbooks point out if distribution has kurtosis greatest than 3, is leptokurtic and then it could has fat-tails. This approach has a broad discution, because it is not necessarilly true <a href='http://www.columbia.edu/~ld208/psymeth97.pdf'>(see DeCarlo, 1997)</a>.

# EVT (Extreme Value Theory)

This is a field into statistics, where the main object of study are events in more unusually large or small levels of a random variable <a href='http://www.dii.uchile.cl/~ceges/publicaciones/ceges51.pdf'>(Fernandez, 2003)</a>. This techniques were developed initially in hydrology and engineering, and after was extended to financial field.

This field is a broad topic in statistics where we can find some distributions with fat-tails, nevertheles, in this case to financial risk management, we point out one of the most representative fat-tailed distributions. This is the Pareto distribution. This was a distribution developed by Vilfrido Pareto, and is used to describe the distribution of incomes (this could be related to Pareto Law).

After Pareto distribution, a generalized distribution was developed and it very useful, named Generalized Pareto Distribution (GPD). It is an important distribution in EVT, because using this we could complete the Balkema and de Haan theorem, and using a threshold analyze the tails distribution, <a href='http://www.iam.fmph.uniba.sk/institute/jurca/qrm/Chapter4.pdf'>(see Jurca, of Univerzita Komensheko, chapter 4)</a>. The aim of using a threshold is to separate only values considered as extrem values from the other values, in random variable distribution. This let to work with a model which describe them, and just them <a href='https://link.springer.com/book/10.1007/978-1-4471-3675-0'>(see Coles, 2001, pag. 78)</a>. A method which give to us the tools to do it, is named Peak Over Threshold Method (POT-method)  <a href='http://www.diva-portal.org/smash/get/diva2:1231783/FULLTEXT01.pdf'>(see Rydman, 2018)</a>.

The GPD function is defined by:<br><br>
$F(x) = 1 - \left( 1 - \frac{\xi x}{\sigma}\right)^\frac{1}{\xi}$<br><br>
As you can see above, it has two parameters, called <b>$\xi$</b> which gives the shape to distribution and <b>$\sigma$</b> which is defined as the scale parameter in the Pareto distribution.

## Threshold setting

As we said before, this approach is looking to describe the tails behaviour. To do this task, is useful POT-method, to determine data which are in tails to model them. This step is important because this involves to set a balance between bias and variance <a href='https://ine.pt/revstat/pdf/rs120102.pdf'>(see Scarrott & MacDonald, 2012)</a>. Quoting Scarrott, et al., <i>"The threshold must be sufficiently high to ensure that the asymptotics underlying the GPD approximation are reliable, thus reducing the bias. However, the reduced sample size for high thresholds increases the variance of the parameter estimates."</i>

Following Coles (2001), we need to calculate the threshold excess, wich is the distance between data points above threshold and the threshold, but this must be testing different thresholds. The goal with this is to identify what is the point <b>(threshold, mean excess)</b> which break an aproximatelly linear behaviour.

We did take negative returns in positive sign of the last nearest year.


```python
prices = prices[-252:] # Last year
```


```python
negative_returns = prices[prices['return'] < 0][['return']] * -1
attempts_ = 40
step_ = (negative_returns.max().values[0] - negative_returns.min().values[0]) / attempts_
```


```python
print('Min\t\t:\t',negative_returns.min().values[0])
print('Max\t\t:\t',negative_returns.max().values[0])
print('Attempts\t:\t',attempts_)
print('Step size\t:\t',step_)
```

    Min		:	 0.008271298593887089
    Max		:	 3.688558109102802
    Attempts	:	 40
    Step size	:	 0.09200717026272287



```python
mean_residual_life = pd.DataFrame(columns=['threshold','threshold_excess', 'quantity'])

for i in range(attempts_):
    threshold_ = negative_returns.min().values[0] + (i*step_)
    negative_returns_ = negative_returns[negative_returns['return'] > threshold_]
    negative_returns_['threshold_excess'] = negative_returns_['return'] - threshold_
    
    mean_residual_life.loc[len(mean_residual_life)] = [
                                                        threshold_,
                                                        negative_returns_['threshold_excess'].mean(),
                                                        negative_returns_.shape[0]
                                                        ]
    del negative_returns_, threshold_
```


```python
mean_residual_life.head(10)
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>threshold</th>
      <th>threshold_excess</th>
      <th>quantity</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0.008271</td>
      <td>0.765193</td>
      <td>114.0</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0.100278</td>
      <td>0.706617</td>
      <td>109.0</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0.192286</td>
      <td>0.727377</td>
      <td>93.0</td>
    </tr>
    <tr>
      <th>3</th>
      <td>0.284293</td>
      <td>0.746218</td>
      <td>80.0</td>
    </tr>
    <tr>
      <th>4</th>
      <td>0.376300</td>
      <td>0.700576</td>
      <td>75.0</td>
    </tr>
    <tr>
      <th>5</th>
      <td>0.468307</td>
      <td>0.734695</td>
      <td>63.0</td>
    </tr>
    <tr>
      <th>6</th>
      <td>0.560314</td>
      <td>0.730416</td>
      <td>56.0</td>
    </tr>
    <tr>
      <th>7</th>
      <td>0.652321</td>
      <td>0.769114</td>
      <td>47.0</td>
    </tr>
    <tr>
      <th>8</th>
      <td>0.744329</td>
      <td>0.805886</td>
      <td>40.0</td>
    </tr>
    <tr>
      <th>9</th>
      <td>0.836336</td>
      <td>0.874501</td>
      <td>33.0</td>
    </tr>
  </tbody>
</table>
</div>




```python
plt.figure(figsize=(15,4))

threshold_selected_ = 0.560314

plt.title('Mean Residual Life', fontsize=20)
plt.plot(mean_residual_life['threshold'], mean_residual_life['threshold_excess'])
plt.axvline(x=threshold_selected_, color='r', linestyle='--')
plt.ylabel('Threshold Excess')
plt.xlabel('Threshold')
plt.show()
```


![png](output_26_0.png)


The Mean Residual Life, designed by Coles (2001) did say us the threshold to capture the data which was used to determine the $\xi$ and $\sigma$ parameters in Generalized Pareto Distribution. <i>Initially, and for now, the selection was done graphically, saying with this which for future works of this subject, we will improve this aspect including some metric or matematical procedure to identify this threshold point</i>.

## Parameters Estimation

Having seen a very brief introduction of EVT before, we cuould say that is necessary to get two fundamental parameters to solve GPD, being $\sigma$ as scale parameter and $\xi$ as shape parameter in GPD distribution. This parameters could be resolved by maximum likelihood method, as was described by Grimshaw (Computing maximum likelihood estimates for the generalized pareto distribution, 1993). But this parameters don't have a closed-form solution <a href='https://digitalcommons.wayne.edu/cgi/viewcontent.cgi?article=2608&context=jmasm'>(see Pahm & Tsokos & Choi, 2019)</a>. Because it we did get the parameters of GPD using genpareto function in <b>scipy.stats</b> python package. This function returns shape $\xi$, location $\mu$, and scale $\sigma$


```python
shape, location, scale = genpareto.fit(
                            negative_returns[
                                (~negative_returns['return'].isnull())
                                &
                                (negative_returns['return'] >= threshold_selected_)
                            ]['return'].values.tolist()
                            )
```


```python
print('Shape\t\t:',shape)
print('Location\t:',location)
print('Scale\t\t:',scale)
```

    Shape		: 0.17739604369840437
    Location	: 0.5660822370796804
    Scale		: 0.6028947337670145


# Value at Risk (VaR)

## EVT

As was pointed out by Fernandez (2003), an estimate VaR-EVT is defined as:

$\hat{VaR} = \mu + \frac{\hat{\beta}}{\hat{\xi}}\left( \left( \alpha\frac{N}{N_u} \right)^{-\xi}-1 \right)$

In this formula the parameters $N_u$ is the number of data points whose returns are above threshold, $N$ is the size of returns including negative and positive returns and $\alpha$ parameter is the significance level. The $\mu$ parameter is not the mean, so it should not be confused with $\mu_{parametricVaR}$


```python
# nu_ is the size of negative returns which are bigger, than threshold
nu_ = negative_returns[
            (~negative_returns['return'].isnull())
            &
            (negative_returns['return'] >= threshold_selected_)
        ].shape[0]

# n_ is the size of returns
n_ = prices.shape[0]
```


```python
def calculate_var_evt(location, scale, shape, n, nu, significance):
    var_evt = location + (scale / shape) * ( math.pow(significance * n  / nu,-shape) - 1)
    return var_evt
```


```python
evt_test = pd.DataFrame(columns=['significance_level', 'var_evt'])
for significance_i in np.arange(0.005,0.07,0.005).tolist():
    var_evt = calculate_var_evt(location=location, scale=scale, shape=shape, n=n_, nu=nu_, significance=significance_i)
    evt_test.loc[len(evt_test)] = [significance_i, var_evt]
    del var_evt
```


```python
evt_test
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>significance_level</th>
      <th>var_evt</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0.005</td>
      <td>3.829643</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0.010</td>
      <td>3.058818</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0.015</td>
      <td>2.649949</td>
    </tr>
    <tr>
      <th>3</th>
      <td>0.020</td>
      <td>2.377179</td>
    </tr>
    <tr>
      <th>4</th>
      <td>0.025</td>
      <td>2.174983</td>
    </tr>
    <tr>
      <th>5</th>
      <td>0.030</td>
      <td>2.015617</td>
    </tr>
    <tr>
      <th>6</th>
      <td>0.035</td>
      <td>1.884838</td>
    </tr>
    <tr>
      <th>7</th>
      <td>0.040</td>
      <td>1.774407</td>
    </tr>
    <tr>
      <th>8</th>
      <td>0.045</td>
      <td>1.679148</td>
    </tr>
    <tr>
      <th>9</th>
      <td>0.050</td>
      <td>1.595606</td>
    </tr>
    <tr>
      <th>10</th>
      <td>0.055</td>
      <td>1.521366</td>
    </tr>
    <tr>
      <th>11</th>
      <td>0.060</td>
      <td>1.454678</td>
    </tr>
    <tr>
      <th>12</th>
      <td>0.065</td>
      <td>1.394234</td>
    </tr>
  </tbody>
</table>
</div>



## Parametric

The simple case of parametric VaR, consist in take the assumption, commonly taught in finance field, where asset returns have normal distribution. Before we said this assumption make difficult some analysis within fat-tails, and this is the reason to calculate this, to take a view of that. The calculous formula is:

$\hat{VaR} = \mu + \sigma Z_\alpha$

Where $\mu$ is the mean of returns, $\sigma$ is the standar deviation of returns and $Z_\alpha$ is the standarized value at a $\alpha$ significance level.


```python
mean_ = prices['return'].mean()
std_ = prices['return'].std()
```


```python
def calculate_var_parametric(mean, std, significance):
    var_par = mean + std * norm.ppf(significance, loc=0, scale=1)
    return var_par
```


```python
parametric_test = pd.DataFrame(columns=['significance_level', 'var_parametric'])
for significance_i in np.arange(0.005,0.07,0.005).tolist():
    var_parametric = calculate_var_parametric(mean=mean_, std=std_, significance=significance_i)
    parametric_test.loc[len(parametric_test)] = [significance_i, -var_parametric]
    del var_parametric
```


```python
parametric_test
```




<div>
<style scoped>
    .dataframe tbody tr th:only-of-type {
        vertical-align: middle;
    }

    .dataframe tbody tr th {
        vertical-align: top;
    }

    .dataframe thead th {
        text-align: right;
    }
</style>
<table border="1" class="dataframe">
  <thead>
    <tr style="text-align: right;">
      <th></th>
      <th>significance_level</th>
      <th>var_parametric</th>
    </tr>
  </thead>
  <tbody>
    <tr>
      <th>0</th>
      <td>0.005</td>
      <td>2.639238</td>
    </tr>
    <tr>
      <th>1</th>
      <td>0.010</td>
      <td>2.371989</td>
    </tr>
    <tr>
      <th>2</th>
      <td>0.015</td>
      <td>2.204604</td>
    </tr>
    <tr>
      <th>3</th>
      <td>0.020</td>
      <td>2.079977</td>
    </tr>
    <tr>
      <th>4</th>
      <td>0.025</td>
      <td>1.979513</td>
    </tr>
    <tr>
      <th>5</th>
      <td>0.030</td>
      <td>1.894704</td>
    </tr>
    <tr>
      <th>6</th>
      <td>0.035</td>
      <td>1.820916</td>
    </tr>
    <tr>
      <th>7</th>
      <td>0.040</td>
      <td>1.755331</td>
    </tr>
    <tr>
      <th>8</th>
      <td>0.045</td>
      <td>1.696105</td>
    </tr>
    <tr>
      <th>9</th>
      <td>0.050</td>
      <td>1.641962</td>
    </tr>
    <tr>
      <th>10</th>
      <td>0.055</td>
      <td>1.591978</td>
    </tr>
    <tr>
      <th>11</th>
      <td>0.060</td>
      <td>1.545466</td>
    </tr>
    <tr>
      <th>12</th>
      <td>0.065</td>
      <td>1.501898</td>
    </tr>
  </tbody>
</table>
</div>



## Comparison


```python
df_test = pd.merge(
                evt_test,
                parametric_test,
                on=['significance_level'],
                how='outer'
            )

df_test['differences'] = df_test['var_evt'] - df_test['var_parametric']
```


```python
df_test.to_csv('datasource/results/EVT/evt_results.csv', index=False)
```


```python
plt.figure(figsize=(15,7))

plt.subplot(2,1,1)
plt.plot(df_test['significance_level'], df_test['var_evt'], label='VaR-EVT')
plt.plot(df_test['significance_level'], df_test['var_parametric'], label='VaR-parametric')
plt.title('Value at Risk - VaR', fontsize=20)
plt.ylabel('VaR (%)')
plt.legend()

plt.subplot(2,1,2)
plt.plot(df_test['significance_level'], df_test['differences'], label='Difference EVT-parametric')
plt.axhline(y=0, color='r', linestyle='dotted', alpha=0.7, label='Zero-level')
plt.ylabel('Difference EVT-param (%)')
plt.xlabel('Significance Level')
plt.legend()

plt.show()
```


![png](output_48_0.png)


# Conclusion

Comparing two methods to calculate VaR, we found the EVT method give us a biggest level of losses than parametric, but not in all significance levels. Was particularly interesting to see the difference between EVT output substracting parametric output at the same significance level, tend to be lower, passing throught zero nearest 5% significance level. Nevertheless, as was described by XXXX, "VaR calculated from EVT will be bigger than historical-simulation VaR and normal VaR, especially at high confidence levels.." <a href='https://www.amazon.com/Enterprise-Risk-Analytics-Capital-Markets/dp/1491744928'>(see Reddy, 2014, page 158)</a>

# Bibliography

* <b>Coles, S. (2001)</b>. An introduction to statistical modeling extreme values.
* <b>DeCarlo, L. (1997)</b>. On the meaning and use of kurtosis. American psycological association, Inc.
* <b>Fernandez, V. (2003)</b>. Extreme value theory: Value at risk and returns dependence around the world.
* <b>Jurca, P. (2019)</b>. Course cuantitative methods of risk management. Univerzita Komensheko.
* <b>Pham, M. & Tsokos, C. & Choi, B. (2019)</b>. Maximum likelihood estimation for the generalized pareto distribution and goodness of fit test with censored data. Vol, 17. Number 2.
* <b>Reddy, R. (2014)</b>. Enterprise risk analytics for capital markets: proactive and real-time risk management.
* <b>Rydman, M. (2018)</b>. Application of the Peak-Over-Threshold method on insurance data.
* <b>Scarrott, C. & MacDonald, A. (2012)</b>. A review of extreme value threshold estimation and uncertainty quantification. Vol, 10. Number 1.

<hr>

This could not to be the final version, so if you have some recommendation or comment about this, I will be grateful to hear it, using e-mail <b>craquinterogo@unal.edu.co</b> or <b>cristian.quintero@est.uexternado.edu.co</b>
