import json
import os
import numpy as np

# We used np.nan in the source strings above, but for JSON serialization we need to be careful.
# Actually, the source is just a string, so 'np.nan' is literally the text "np.nan".

notebook = {
 "cells": [
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "# Lab Experiment 2: Data Pre-Processing"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "import pandas as pd\n",
    "import numpy as np\n",
    "import matplotlib.pyplot as plt\n",
    "import seaborn as sns\n",
    "from sklearn.preprocessing import MinMaxScaler, StandardScaler\n",
    "from sklearn.decomposition import PCA"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Creating a DataFrame\n",
    "data = {\n",
    "    'Name': ['Alice', 'Bob', 'Charlie', 'David', 'Alice', 'Eve', 'Frank', 'Grace', 'Heidi', 'Ivan'],\n",
    "    'Age': [25, 30, 35, 40, 25, 22, np.nan, 29, 30, 31],\n",
    "    'Salary': [50000, 60000, 70000, 80000, 50000, 45000, 52000, 58000, 61000, 63000],\n",
    "    'Score': [85, 90, 95, np.nan, 85, 88, 92, 89, 91, 87],\n",
    "    'Height': [165, 170, 175, 180, 165, 160, 172, 168, 171, 173],\n",
    "    'Weight': [60, 70, 80, 90, 60, 55, 75, 65, 72, 74]  # High correlation with Height\n",
    "}\n",
    "df = pd.DataFrame(data)\n",
    "df"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Cleaning: Handling Missing Values\n",
    "print(\"Original Shape:\", df.shape)\n",
    "df_cleaned = df.dropna()\n",
    "print(\"Shape after dropping missing values:\", df_cleaned.shape)\n",
    "# Re-index after dropna is good practice but keeping it simple as requested\n",
    "df_cleaned"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Integration: Removing Duplicates\n",
    "# Note: In our synthetic data, row 0 and row 4 are identical ('Alice', 25, ...)\n",
    "df_no_duplicates = df_cleaned.drop_duplicates()\n",
    "print(\"Shape after removing duplicates:\", df_no_duplicates.shape)\n",
    "df_no_duplicates"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Transformation: Normalization (Min-Max Scaling)\n",
    "scaler = MinMaxScaler()\n",
    "df_normalized = df_no_duplicates.copy()\n",
    "# Transforming numerical columns\n",
    "cols_to_scale = ['Age', 'Salary', 'Score', 'Height', 'Weight']\n",
    "df_normalized[cols_to_scale] = scaler.fit_transform(df_normalized[cols_to_scale])\n",
    "df_normalized.head()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Transformation: Standardization (Z-Score)\n",
    "scaler_z = StandardScaler()\n",
    "df_zscore = df_no_duplicates.copy()\n",
    "df_zscore[cols_to_scale] = scaler_z.fit_transform(df_zscore[cols_to_scale])\n",
    "df_zscore.head()"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Smoothening: Binning\n",
    "# Let's bin 'Age' into categories\n",
    "bins = [0, 30, 40, 100]\n",
    "labels = ['Young', 'Middle-aged', 'Senior']\n",
    "df_binned = df_no_duplicates.copy()\n",
    "df_binned['Age_Group'] = pd.cut(df_binned['Age'], bins=bins, labels=labels)\n",
    "df_binned[['Age', 'Age_Group']]"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Data Reduction: PCA\n",
    "# Using all numerical features to reduce to 2 components\n",
    "pca = PCA(n_components=2)\n",
    "features = df_no_duplicates[cols_to_scale]\n",
    "pca_result = pca.fit_transform(features)\n",
    "df_pca = pd.DataFrame(data=pca_result, columns=['PC1', 'PC2'])\n",
    "df_pca.head()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "## Theory: Pearson Correlation"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Pearson Correlation: NumPy Implementation\n",
    "# Using Height and Weight as example\n",
    "height = df_no_duplicates['Height']\n",
    "weight = df_no_duplicates['Weight']\n",
    "correlation_matrix_np = np.corrcoef(height, weight)\n",
    "print(\"Correlation Matrix (NumPy):\\n\", correlation_matrix_np)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Pearson Correlation: Pandas Implementation\n",
    "correlation_matrix_pd = df_no_duplicates[['Height', 'Weight']].corr(method='pearson')\n",
    "print(\"Correlation Matrix (Pandas):\\n\", correlation_matrix_pd)"
   ]
  },
  {
   "cell_type": "code",
   "execution_count": None,
   "metadata": {},
   "outputs": [],
   "source": [
    "# Visualization: Heatmap of Correlation Matrix\n",
    "plt.figure(figsize=(8, 6))\n",
    "sns.heatmap(df_no_duplicates[cols_to_scale].corr(), annot=True, cmap='coolwarm')\n",
    "plt.title('Correlation Matrix Heatmap')\n",
    "plt.show()"
   ]
  },
  {
   "cell_type": "markdown",
   "metadata": {},
   "source": [
    "## Conclusion\n",
    "\n",
    "Data preprocessing is a critical step in the data mining process. It involves cleaning, integrating, transforming, and reducing data to make it suitable for analysis. In this lab, we successfully demonstrated techniques for handling missing values, removing duplicates, normalizing data using Min-Max and Z-score methods, binning for data smoothing, and applying PCA for dimensionality reduction. We also explored correlation analysis using Pearson's method and visualized the relationships using heatmaps.\n",
    "\n",
    "## FAQs\n",
    "\n",
    "1. **Why do we need scaling?**\n",
    "   Scaling ensures that features with different units and ranges contribute equally to the analysis, preventing features with larger magnitudes from dominating the model.\n",
    "\n",
    "2. **Benefits and Techniques of Binning in Python**\n",
    "   Binning smooths noisy data, handles outliers, and can improve model performance by grouping continuous values into discrete categories. Techniques include equal-width binning and equal-frequency binning.\n",
    "\n",
    "3. **What is Data leakage, how to avoid any data leakage during the model testing process.**\n",
    "   Data leakage occurs when information from the target variable is used to train the model. To avoid it, ensure that data preprocessing (like scaling) is fit only on the training set and then applied to the test set.\n",
    "\n",
    "4. **Which technique we should use Normalization or Standardization?**\n",
    "   Normalization (Min-Max) is useful when the data needs to be bounded (e.g., 0-1) and for algorithms like Neural Networks. Standardization (Z-score) is better when the data follows a Gaussian distribution and for algorithms like SVMs and Logistic Regression.\n",
    "\n",
    "5. **What are the benefits of Correlation Analysis?**\n",
    "   It helps in identifying relationships between variables, detecting multicollinearity, and selecting relevant features for the model.\n",
    "\n",
    "6. **What is the significance of Correlation Analysis?**\n",
    "   It quantifies the strength and direction of the linear relationship between two variables, aiding in understanding data structure and feature selection.\n",
    "\n",
    "7. **What are the different kinds of correlation analysis? Discuss their strength and weakness.**\n",
    "   - **Pearson:** Measures linear relationship. Sensitive to outliers.\n",
    "   - **Spearman:** Measures monotonic relationship. Robust to outliers but less powerful for linear relationships.\n",
    "   - **Kendall:** Measures ordinal association. computationally expensive but robust.\n",
    "\n",
    "8. **What are the factors that affect a Correlation Analysis?**\n",
    "   Outliers, non-linear relationships, restricted range of data, and heterogeneous subgroups can affect correlation analysis.\n",
    "\n",
    "9. **Write a short note on**\n",
    "   - **a. The correlation coefficient:** A statistical measure (r) that calculates the strength of the relationship between the relative movements of two variables. It ranges from -1 to +1.\n",
    "   - **b. The p-value:** A probability measure that helps determine the significance of the results. A low p-value (typically < 0.05) indicates that the observed correlation is statistically significant."
   ]
  }
 ],
 "metadata": {
  "kernelspec": {
   "display_name": "Python 3",
   "language": "python",
   "name": "python3"
  },
  "language_info": {
   "codemirror_mode": {
    "name": "ipython",
    "version": 3
   },
   "file_extension": ".py",
   "mimetype": "text/x-python",
   "name": "python",
   "nbconvert_exporter": "python",
   "pygments_lexer": "ipython3",
   "version": "3.8.5"
  }
 },
 "nbformat": 4,
 "nbformat_minor": 4
}

with open('Lab_Experiment_2.ipynb', 'w') as f:
    json.dump(notebook, f, indent=1)
    
print("Notebook created successfully.")
